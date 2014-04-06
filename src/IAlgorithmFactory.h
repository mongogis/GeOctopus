#ifndef HPGC_INTERFACE_FACTORY_H_INCLUDE

#define HPGC_INTERFACE_FACTORY_H_INCLUDE

#include "IAlgorithm.h"

namespace hpgc{

	class IAlgorithmFactory
	{
	public:
		virtual IAlgorithm  * Create(int argc, char ** argv) = 0;
		virtual const char * GetName() = 0;
	};

}

#endif