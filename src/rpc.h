#ifndef RPC_h__
#define RPC_h__

#include "VectorBarrel.h"

#include <google/protobuf/message.h>
#include <functional>
#include <list>
#include <vector>
#include <deque>
#include <string>
#include <thread>
#include <mutex>
#include <unordered_set>
#include <array>
#include <mpi.h>

namespace hpgc {

    typedef google::protobuf::Message Message;

    int ANY_SOURCE = MPI::ANY_SOURCE;
    int ANY_TAG = MPI::ANY_TAG;

    struct RPCInfo {
        int target;
        int source;
        int tag;
    };

    struct Header {
        Header() : is_reply(false) {}
        bool is_reply;
    };

    struct RPCRequest {
        int target;
        int rpc_type;
        int failures;

        std::string payload;
        MPI::Request mpi_req;
        MPI::Status status;
        double start_time;

        RPCRequest(int target, int method, const Message & msg, Header h = Header());
        ~RPCRequest();

        bool Finished();
        double Elapsed();
    };

    typedef std::function<void(const RPCInfo & rpc)> Callback;

    struct CallbackInfo {
        Message * request;
        Message * response;

        Callback call;

        bool spawn_thread;
    };

    extern int ANY_SOURCE;
    extern int ANY_TAG;

    class RPCNetwork {
    public:
        bool active() const;
        int64_t pending_bytes() const;

        // Blocking read for the given source and message type.
        void Read(int desired_src, int type, Message * data, int * source = NULL);
        bool TryRead(int desired_src, int type, Message * data, int * source = NULL);

        // Enqueue the given request for transmission.
        void Send(RPCRequest * req);
        void Send(int dst, int method, const Message & msg);

        void Broadcast(int method, const Message & msg);
        void SyncBroadcast(int method, const Message & msg);
        void WaitForSync(int method, int count);

        // Invoke 'method' on the destination, and wait for a reply.
        void Call(int dst, int method, const Message & msg, Message * reply);

        void Flush();
        void Shutdown();

        int id() { return id_; }
        int size() const;

        static RPCNetwork * Get();
        static void Init();


        // Register the given function with the RPC thread.  The function will be invoked
        // from within the network thread whenever a message of the given type is received.
        typedef std::function<void(const RPCInfo & rpc)> Callback;

        // Use RegisterCallback(...) instead.
        void _RegisterCallback(int req_type, Message * req, Message * resp,
                               Callback cb);

        // After registering a callback, indicate that it should be invoked in a
        // separate thread from the RPC server.
        void SpawnThreadFor(int req_type);

        struct CallbackInfo {
            Message * req;
            Message * resp;

            Callback call;

            bool spawn_thread;
        };

    private:
        static const int kMaxHosts = 512;
        static const int kMaxMethods = 64;

        typedef std::deque<std::string> Queue;

        bool running;

        std::array<CallbackInfo *, kMaxMethods> callbacks_;

        std::vector<RPCRequest *> pending_sends_;
        std::unordered_set<RPCRequest *> active_sends_;

        Queue requests[kMaxMethods][kMaxHosts];
        Queue replies[kMaxMethods][kMaxHosts];

        MPI::Comm * world_;
        mutable std::recursive_mutex send_lock;
        mutable std::recursive_mutex q_lock[kMaxHosts];
        mutable std::thread * t_;
        int id_;

        bool check_reply_queue(int src, int type, Message * data);
        bool check_request_queue(int src, int type, Message * data);

        void InvokeCallback(CallbackInfo * ci, RPCInfo rpc);
        void CollectActive();
        void Run();

        RPCNetwork();
    };

    using namespace std::placeholders;

    template <class Request, class Response, class Function, class Klass>
    void RegisterCallback(int req_type, Request * req, Response * resp,
                          Function function, Klass klass) {
        RPCNetwork::Get()->_RegisterCallback(req_type, req, resp, std::bind(function,
                                             klass, std::cref(*req), resp, _1));
    }

}

#endif // RPC_h__
