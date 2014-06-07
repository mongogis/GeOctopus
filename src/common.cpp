#include "common.h"
#include "rpc.h"

namespace hpgc{
	void HPGCInit(int argc, const char ** argv){
		RPCNetwork::Init();
	}
}

