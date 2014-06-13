#include "rpc.h"
#include "rpc.message.pb.h"
#include "port.debug.h"
#include "timer.h"
#include "common.h"

#include <algorithm>
#include <stdlib.h>
#include <iostream>


#define FLAGS_sleep_time 1


namespace hpgc {

    int ANY_SOURCE = MPI::ANY_SOURCE;
    int ANY_TAG = MPI::ANY_TAG;

    RPCRequest::RPCRequest(int target, int method, const Message & msg, Header h ) {
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

    RPCNetwork::RPCNetwork() {
        if (!getenv("OMPI_COMM_WORLD_RANK")) {
            m_word = nullptr;
            m_id = -1;
            m_running = false;
            return;
        }
        MPI::Init_thread(MPI_THREAD_SINGLE);
        m_word = &MPI::COMM_WORLD;
        m_running = 1;
        m_thread = new std::thread(&RPCNetwork::Run, this);
        m_id = m_word->Get_rank();
        m_callbacks.fill(nullptr);
    }

    bool RPCNetwork::Active() const {
        return m_active_sends.size() + m_pending_sends.size() > 0;
    }

    int RPCNetwork::Id() const{
	return m_word->Get_rank();
    }

    int RPCNetwork::Size() const {
        return m_word->Get_size();
    }

    int64_t RPCNetwork::Pending_bytes() const {
        std::lock_guard<std::recursive_mutex> sl(m_send_lock);
        int64_t t = 0;
        std::for_each(m_active_sends.cbegin(), m_active_sends.cend(),
        [&t](const RPCRequest * it) { t += it->payload.size(); }
                     );
        std::for_each(m_pending_sends.cbegin(), m_pending_sends.cend(),
        [&t](const RPCRequest * it) { t += it->payload.size(); }
                     );
        return t;
    }

    void RPCNetwork::CollectActive() {
        if (m_active_sends.empty())
            return;
        std::lock_guard<std::recursive_mutex> sl(m_send_lock);
        std::unordered_set<RPCRequest *>::iterator i = m_active_sends.begin();
        while (i != m_active_sends.end()) {
            RPCRequest * r = (*i);
            if (r->Finished()) {
                delete r;
                i = m_active_sends.erase(i);
                continue;
            }
            ++i;
        }
    }

    void RPCNetwork::InvokeCallback(CallbackInfo * ci, RPCInfo rpc) {
        ci->call(rpc);
        Header reply_header;
        reply_header.is_reply = true;
        Send(new RPCRequest(rpc.source, rpc.tag, *ci->response, reply_header));
    }

    void RPCNetwork::Run() {
        while (m_running) {
            MPI::Status st;
            if (m_word->Iprobe(hpgc::ANY_SOURCE, hpgc::ANY_TAG, st)) {
                int tag = st.Get_tag();
                int source = st.Get_source();
                int bytes = st.Get_count(MPI::BYTE);

                std::string data;
                data.resize(bytes);
                m_word->Recv(&data[0], bytes, MPI::BYTE, source, tag, st);
                Header * h = (Header *)&data[0];
                if (h->is_reply) {
                    std::lock_guard<std::recursive_mutex> sl(m_q_lock[tag]);
                    m_replies[tag][source].push_back(data);
                }
                else {
                    if (m_callbacks[tag] != nullptr) {
                        CallbackInfo * ci = m_callbacks[tag];
                        ci->request->ParseFromArray(&data[0] + sizeof(Header),
                                                data.size() - sizeof(Header));
                        RPCInfo rpc = { source, Id(), tag };
                        if (ci->spawn_thread) {
                            std::thread(std::bind(&RPCNetwork::InvokeCallback, this, ci, rpc));
                        }
                        else {
                            ci->call(rpc);
                            Header reply_header;
                            reply_header.is_reply = true;
                            Send(new RPCRequest(source, tag, *ci->response, reply_header));
                        }
                    }
                    else {
                        std::lock_guard<std::recursive_mutex> sl(m_q_lock[tag]);
                        m_requests[tag][source].push_back(data);
                    }
                }
            }
            else {
                Sleep(FLAGS_sleep_time);
            }

            while (!m_pending_sends.empty()) {
                std::lock_guard<std::recursive_mutex> sl(m_send_lock);
                RPCRequest * s = m_pending_sends.back();
                m_pending_sends.pop_back();
                s->start_time = Now();
                s->mpi_req = m_word->Issend(
                                 s->payload.data(), s->payload.size(), MPI::BYTE, s->target, s->rpc_type);
                m_active_sends.insert(s);
            }
            CollectActive();
        }
    }

    bool RPCNetwork::check_request_queue(int src, int type, Message * data) {
        Queue & q = m_requests[type][src];
        if (!q.empty()) {
            std::lock_guard<std::recursive_mutex> sl(m_q_lock[type]);
            if (q.empty())
                return false;
            const std::string & s = q.front();
            if (data) {
                data->ParseFromArray(s.data() + sizeof(Header), s.size() - sizeof(Header));
            }
            q.pop_front();
            return true;
        }
        return false;
    }

    bool RPCNetwork::check_reply_queue(int src, int type, Message * data) {
        Queue & q = m_replies[type][src];
        if (!q.empty()) {
            std::lock_guard<std::recursive_mutex> sl(m_q_lock[type]);
            if (q.empty())
                return false;
            const std::string & s = q.front();
            if (data) {
                data->ParseFromArray(s.data() + sizeof(Header), s.size() - sizeof(Header));
            }
            q.pop_front();
            return true;
        }
        return false;
    }

    // Blocking read for the given source and message type.
    void RPCNetwork::Read(int desired_src, int type, Message * data, int * source) {
        Timer t;
        while (!TryRead(desired_src, type, data, source)) {
            Sleep(FLAGS_sleep_time);
        }
    }

    bool RPCNetwork::TryRead(int src, int type, Message * data, int * source) {
        if (src == hpgc::ANY_SOURCE) {
            for (int i = 0; i < m_word->Get_size(); ++i) {
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

    void RPCNetwork::Call(int dst, int method, const Message & msg,
                          Message * reply) {
        Send(dst, method, msg);
        Timer t;
        while (!check_reply_queue(dst, method, reply)) {
            Sleep(FLAGS_sleep_time);
        }
    }

    // Enqueue the given request for transmission.
    void RPCNetwork::Send(RPCRequest * req) {
        std::lock_guard<std::recursive_mutex> sl(m_send_lock);
        //    LOG(INFO) << "Sending... " << MP(req->target, req->rpc_type);
        m_pending_sends.push_back(req);
    }

    void RPCNetwork::Send(int dst, int method, const Message & msg) {
        RPCRequest * r = new RPCRequest(dst, method, msg);
        Send(r);
    }

    void RPCNetwork::Shutdown() {
        if (m_running) {
            Flush();
            m_running = false;
            MPI_Finalize();
        }
    }

    void RPCNetwork::Flush() {
        while (Active()) {
            Sleep(FLAGS_sleep_time);
        }
    }

    void RPCNetwork::Broadcast(int method, const Message & msg) {
        for (int i = 1; i < m_word->Get_size(); ++i) {
            Send(i, method, msg);
        }
    }

    void RPCNetwork::SyncBroadcast(int method, const Message & msg) {
        Broadcast(method, msg);
        WaitForSync(method, m_word->Get_size() - 1);
    }

    void RPCNetwork::WaitForSync(int method, int count) {
        EmptyMessage empty;
        std::unordered_set<int> pending;
        for (int i = 1; i < m_word->Get_size(); ++i) {
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

    void RPCNetwork::Barrier(){
       m_word->Barrier(); 
    }

    void RPCNetwork::_RegisterCallback(int message_type, Message * req,
                                       Message * resp, Callback cb) {
        CallbackInfo * cbinfo = new CallbackInfo;
        cbinfo->spawn_thread = false;
        cbinfo->request = req;
        cbinfo->response = resp;
        cbinfo->call = cb;
        m_callbacks[message_type] = cbinfo;
    }

    void RPCNetwork::SpawnThreadFor(int req_type) {
        m_callbacks[req_type]->spawn_thread = true;
    }

    static RPCNetwork * net = nullptr;
    RPCNetwork * RPCNetwork::Get() {
        return net;
    }

    static void ShutdownMPI() {
        RPCNetwork::Get()->Shutdown();
    }

    void RPCNetwork::Init() {
        net = new RPCNetwork();
        atexit(&ShutdownMPI);
    }



}// hpgc_name_space

