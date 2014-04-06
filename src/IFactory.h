#ifndef HPGC_INTERFACE_FACTORY_H_INCLUDE

#define HPGC_INTERFACE_FACTORY_H_INCLUDE

#include "IPartition.h"

namespace hpgc{

	class IFactory
	{
	public:
		virtual IAlgorithm  * Create(int argc, char ** argv) = 0;
	};

}

#endif