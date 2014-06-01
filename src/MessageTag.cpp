#include "MessageTag.h"
#include "port.debug.h"

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
		return 0.1;
	}

	RPCRequest::~RPCRequest()
	{

	}

}

