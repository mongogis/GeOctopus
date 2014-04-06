#ifndef HPGC_SERVER_H_INCLUDE

#define HPGC_SERVER_H_INCLUDE 

#include "port.designpattern.h"
#include "IAlgorithmFactory.h" 

namespace hpgc{

	class Server 
	{
	public:
		IAlgorithmFactory * Create(int argc, char ** argv);
	};
}

#endif