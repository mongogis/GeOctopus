#ifndef RPC_h__
#define RPC_h__

#include "VectorBarrel.h"
#include <mpiobject.h>

#include <google/protobuf/message.h>
#include <functional>
#include <list>
#include <vector>

namespace hpgc{

	typedef google::protobuf::Message Message;

	int ANY_SOURCE = MPI::ANY_SOURCE;
	int ANY_TAG = MPI::ANY_TAG;

	struct RPCInfo
	{
		int target;
		int source;
		int tag;
	};

	struct Header {
		Header() : is_reply(false) {}
		bool is_reply;
	};

	struct RPCRequest
	{
		int target;
		int rpc_type;
		int failures;

		std::string payload;
		MPI::Request mpi_req;
		MPI::Status status;
		double start_time;

		RPCRequest(int target, int method, const Message & msg, Header h);
		~RPCRequest();

		bool Finished();
		double Elapsed();
	};

	typedef std::function<void(const RPCInfo& rpc)> Callback;

	struct CallbackInfo
	{
		Message * request;
		Message * response;

		Callback call;

		bool spawn_thread;
	};

	extern int ANY_SOURCE;
	extern int ANY_TAG;

	class RPCNetwork{
	public:

		void Send(RPCRequest *req);

		static RPCNetwork * Get();
		static void Init();

		void Shutdown();

		int Id();
		int Size();

		void Run();

		RPCNetwork();
		~RPCNetwork();
	
	private:
		static const int kMaxHosts = 512;
		static const int kMaxMethods = 64;

		CallbackInfo* m_callbacks[kMaxMethods];
		std::vector<RPCRequest*> m_pending_sends;
		std::list<RPCRequest * > m_active_sends;

		MPI::Comm * m_world;
		int m_id;
		bool m_running;

		void RegisterCallback(int req_type,Message * req,Message * resp,Callback cb);
		void CollectActive();

	};

	using namespace std::placeholders;

	template <class Request, class Response, class Function, class Klass>
	void RegisterCallback(int req_type, Request *req, Response *resp, Function function, Klass klass) {
		RPCNetwork::Get()->RegisterCallback(req_type, req, resp, std::bind(function, klass, std::cref(*req), resp, _1));
	}

}

#endif // RPC_h__
