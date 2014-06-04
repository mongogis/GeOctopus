#include "rpc.h"
#include "port.debug.h"
#include "timer.h"

#include <port.designpattern.h>
#include <mpioperator.recvmsg.h>
#include <mpioperator.sendmsg.h>


namespace hpgc {

	RPCRequest::RPCRequest(int target, int method, const Message & msg, Header h)
	{
		failures = 0;
		this->target = target;
		rpc_type = method;

		payload.append((char*)&h, sizeof(Header));
		msg.AppendToString(&payload);
	}

	bool RPCRequest::Finished()
	{
		return mpi_req.Test(status);
	}

	double RPCRequest::Elapsed()
	{
		return Now() - start_time;
	}

	RPCRequest::~RPCRequest() {}

	static RPCNetwork * net = nullptr;
	
	RPCNetwork * RPCNetwork::Get(){
		return net;
	}

	static void ShutdownMPI() {
		RPCNetwork::Get()->Shutdown();
	}

	void RPCNetwork::Init(){
		net = new RPCNetwork();
		atexit(&ShutdownMPI);
	}

	void RPCNetwork::RegisterCallback(int req_type, Message * req, Message * resp, Callback cb)
	{
		CallbackInfo *cbinfo = new CallbackInfo;

		cbinfo->spawn_thread = false;
		cbinfo->request = req;
		cbinfo->response = resp;
		cbinfo->call = cb;

		m_callbacks[req_type] = cbinfo;

	}

	RPCNetwork::RPCNetwork()
	{
		if (!getenv("OMPI_COMM_WORLD_RANK")) {
			m_world = nullptr;
			m_id = -1;
			return;
		}

		MPI::Init_thread(MPI_THREAD_SINGLE);

		m_world= &MPI::COMM_WORLD;
		m_running = true;
		m_id = m_world->Get_rank();
		m_thread = new std::thread(&RPCNetwork::Run, this);

		for (int i = 0; i < kMaxMethods; ++i) {
			m_callbacks[i] = nullptr;
		}
	}

	RPCNetwork::~RPCNetwork()
	{

	}

	int RPCNetwork::Id()
	{
		return m_id;
	}

	int RPCNetwork::Size()
	{
		return m_world->Get_size();
	}

	void RPCNetwork::Shutdown()
	{
		MPI_Finalize();
	}

	void RPCNetwork::Run()
	{
		while (m_running)
		{
			MPI::Status status;

			if (m_world->Iprobe(hpgc::ANY_SOURCE, hpgc::ANY_TAG, status)){
				int tag = status.Get_tag();
				int source = status.Get_source();
				int bytes = status.Get_count(MPI::BYTE);

				std::string data;
				data.resize(bytes);

				m_world->Recv(&data[0], bytes, MPI::BYTE, source, tag, status);

				Header * h = (Header *)&data[0];

				if (h->is_reply)
				{
					replies[tag][source].push_back(data);
				}
				else
				{
					if (m_callbacks[tag] != nullptr)
					{
						CallbackInfo * ci = m_callbacks[tag];
						ci->request->ParseFromArray(&data[0] + sizeof(Header), data.size() - sizeof(Header));

						RPCInfo rpc = {source,Id(),tag};
						ci->call(rpc);
						Header reply_header;
						reply_header.is_reply = true;
						Send(new RPCRequest(source, tag, *ci->response, reply_header));
					}
					else
					{
						requests[tag][source].push_back(data);
					}
				}
			}
			else{
				Sleep(2);
			}
		}
	}

	void RPCNetwork::Send(RPCRequest *req)
	{
		req->start_time = Now();
		req->mpi_req = m_world->Issend(req->payload.data(), req->payload.size(), MPI::BYTE, req->target, req->rpc_type);
		m_active_sends.push_back(req);
	}

	

}// hpgc_name_space

