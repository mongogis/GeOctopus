#include "rpc.h"
#include "port.debug.h"
#include "timer.h"
#include "rpc.message.pb.h"

#include <port.designpattern.h>
#include <mpioperator.recvmsg.h>
#include <mpioperator.sendmsg.h>

#define FLAGS_sleep_time 3


namespace hpgc {

    RPCRequest::RPCRequest(int target, int method, const Message & msg, Header h=Header()) {
        failures = 0;
        this->target = target;
        rpc_type = method;
        payload.append((char *)&h, sizeof(Header));
        msg.AppendToString(&payload);
    }

    bool RPCRequest::Finished() {
        return mpi_req.Test(status);
    }

    double RPCRequest::Elapsed() {
        return Now() - start_time;
    }

    RPCRequest::~RPCRequest() {}




	RPCThread::RPCThread() {
		if (!getenv("OMPI_COMM_WORLD_RANK")) {
			world_ = nullptr;
			id_ = -1;
			running = false;
			return;
		}

		MPI::Init_thread(MPI_THREAD_SINGLE);

		world_ = &MPI::COMM_WORLD;
		running = 1;
		t_ = new std::thread(&RPCThread::Run, this);
		id_ = world_->Get_rank();

		for (int i = 0; i < kMaxMethods; ++i) {
			callbacks_[i] = nullptr;
		}
	}

	bool RPCThread::active() const {
		return active_sends_.size() + pending_sends_.size() > 0;
	}

	int RPCThread::size() const {
		return world_->Get_size();
	}

	int64_t RPCThread::pending_bytes() const {
		std::lock_guard<std::recursive_mutex> sl(send_lock);
		int64_t t = 0;

		for (std::unordered_set<RPCRequest*>::const_iterator i = active_sends_.begin(); i != active_sends_.end(); ++i) {
			t += (*i)->payload.size();
		}

		for (int i = 0; i < pending_sends_.size(); ++i) {
			t += pending_sends_[i]->payload.size();
		}

		return t;
	}

	void RPCThread::CollectActive() {
		if (active_sends_.empty())
			return;

		std::lock_guard<std::recursive_mutex> sl(send_lock);
		std::unordered_set<RPCRequest*>::iterator i = active_sends_.begin();
		while (i != active_sends_.end()) {
			RPCRequest *r = (*i);
			if (r->Finished()) {
				delete r;
				i = active_sends_.erase(i);
				continue;
			}
			++i;
		}
	}

	void RPCThread::InvokeCallback(CallbackInfo *ci, RPCInfo rpc) {
		ci->call(rpc);
		Header reply_header;
		reply_header.is_reply = true;
		Send(new RPCRequest(rpc.source, rpc.tag, *ci->resp, reply_header));
	}

	void RPCThread::Run() {
		while (running) {
			MPI::Status st;

			if (world_->Iprobe(hpgc::ANY_SOURCE, hpgc::ANY_TAG, st)) {
				int tag = st.Get_tag();
				int source = st.Get_source();
				int bytes = st.Get_count(MPI::BYTE);

				std::string data;
				data.resize(bytes);

				world_->Recv(&data[0], bytes, MPI::BYTE, source, tag, st);

				Header *h = (Header*)&data[0];

				if (h->is_reply) {
					std::lock_guard<std::recursive_mutex> sl(q_lock[tag]);
					replies[tag][source].push_back(data);
				}
				else {
					if (callbacks_[tag] != nullptr) {
						CallbackInfo *ci = callbacks_[tag];
						ci->req->ParseFromArray(&data[0] + sizeof(Header), data.size() - sizeof(Header));

						RPCInfo rpc = { source, id(), tag };
						if (ci->spawn_thread) {
							std::thread(std::bind(&RPCThread::InvokeCallback, this, ci, rpc));
						}
						else {
							ci->call(rpc);
							Header reply_header;
							reply_header.is_reply = true;
							Send(new RPCRequest(source, tag, *ci->resp, reply_header));
						}
					}
					else {
						std::lock_guard<std::recursive_mutex> sl(q_lock[tag]);
						requests[tag][source].push_back(data);
					}
				}
			}
			else {
				Sleep(FLAGS_sleep_time);
			}

			while (!pending_sends_.empty()) {
				std::lock_guard<std::recursive_mutex> sl(send_lock);
				RPCRequest* s = pending_sends_.back();
				pending_sends_.pop_back();
				s->start_time = Now();
				s->mpi_req = world_->Issend(
					s->payload.data(), s->payload.size(), MPI::BYTE, s->target, s->rpc_type);
				active_sends_.insert(s);
			}

			CollectActive();

		}
	}

	bool RPCThread::check_request_queue(int src, int type, Message* data) {

		Queue& q = requests[type][src];
		if (!q.empty()) {
			std::lock_guard<std::recursive_mutex> sl(q_lock[type]);
			if (q.empty())
				return false;

			const std::string& s = q.front();
			if (data) {
				data->ParseFromArray(s.data() + sizeof(Header), s.size() - sizeof(Header));
			}

			q.pop_front();
			return true;
		}
		return false;
	}

	bool RPCThread::check_reply_queue(int src, int type, Message* data) {

		Queue& q = replies[type][src];
		if (!q.empty()) {
			std::lock_guard<std::recursive_mutex> sl(q_lock[type]);
			if (q.empty())
				return false;

			const std::string& s = q.front();
			if (data) {
				data->ParseFromArray(s.data() + sizeof(Header), s.size() - sizeof(Header));
			}

			q.pop_front();
			return true;
		}
		return false;
	}

	// Blocking read for the given source and message type.
	void RPCThread::Read(int desired_src, int type, Message* data, int *source) {
		Timer t;
		while (!TryRead(desired_src, type, data, source)) {
			Sleep(FLAGS_sleep_time);
		}
	}

	bool RPCThread::TryRead(int src, int type, Message* data, int *source) {
		if (src == hpgc::ANY_SOURCE) {
			for (int i = 0; i < world_->Get_size(); ++i) {
				if (TryRead(i, type, data, source)) {
					return true;
				}
			}
		}
		else {
			if (check_request_queue(src, type, data)) {
				if (source) { *source = src; }
				return true;
			}
		}

		return false;
	}

	void RPCThread::Call(int dst, int method, const Message &msg, Message *reply) {
		Send(dst, method, msg);
		Timer t;
		while (!check_reply_queue(dst, method, reply)) {
			Sleep(FLAGS_sleep_time);
		}
	}

	// Enqueue the given request for transmission.
	void RPCThread::Send(RPCRequest *req) {
		std::lock_guard<std::recursive_mutex> sl(send_lock);
		//    LOG(INFO) << "Sending... " << MP(req->target, req->rpc_type);
		pending_sends_.push_back(req);
	}

	void RPCThread::Send(int dst, int method, const Message &msg) {
		RPCRequest *r = new RPCRequest(dst, method, msg);
		Send(r);
	}

	void RPCThread::Shutdown() {
		if (running) {
			Flush();
			running = false;
			MPI_Finalize();
		}
	}

	void RPCThread::Flush() {
		while (active()) {
			Sleep(FLAGS_sleep_time);
		}
	}

	void RPCThread::Broadcast(int method, const Message& msg) {
		for (int i = 1; i < world_->Get_size(); ++i) {
			Send(i, method, msg);
		}
	}

	void RPCThread::SyncBroadcast(int method, const Message& msg) {
		Broadcast(method, msg);
		WaitForSync(method, world_->Get_size() - 1);
	}

	void RPCThread::WaitForSync(int method, int count) {
		EmptyMessage empty;
		std::unordered_set<int> pending;

		for (int i = 1; i < world_->Get_size(); ++i) {
			pending.insert(i);
		}

		while (!pending.empty()) {
			for (std::unordered_set<int>::iterator i = pending.begin();
				i != pending.end();
				++i) {
				if (check_reply_queue(*i, method, nullptr)) {
					pending.erase(i);
				}
				
			}
			Sleep(FLAGS_sleep_time);
		}
	}

	void RPCThread::_RegisterCallback(int message_type, Message *req, Message* resp, Callback cb) {
		CallbackInfo *cbinfo = new CallbackInfo;

		cbinfo->spawn_thread = false;
		cbinfo->req = req;
		cbinfo->resp = resp;
		cbinfo->call = cb;

		callbacks_[message_type] = cbinfo;
	}

	void RPCThread::SpawnThreadFor(int req_type) {
		callbacks_[req_type]->spawn_thread = true;
	}

	static RPCThread* net = nullptr;
	RPCThread* RPCThread::Get() {
		return net;
	}

	static void ShutdownMPI() {
		RPCThread::Get()->Shutdown();
	}

	void RPCThread::Init() {
		net = new RPCThread();
		atexit(&ShutdownMPI);
	}



}// hpgc_name_space

