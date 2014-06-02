#include "rpc.h"
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
		m_id = m_world->Get_rank();

		for (int i = 0; i < kMaxMethods; ++i) {
			m_callbacks[i] = NULL;
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

	

}

