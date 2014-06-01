#ifndef MessageTag_h__
#define MessageTag_h__

#include "VectorBarrel.h"
#include <mpiobject.h>

#include <google/protobuf/message.h>
#include <functional>

namespace hpgc{

	typedef google::protobuf::Message Message;

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

}

#endif // MessageTag_h__
