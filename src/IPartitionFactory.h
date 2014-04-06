#ifndef HPGC_INTERFACE_PARTITION_FACTORY_H_INCLUDE

#define HPGC_INTERFACE_PARTITION_FACTORY_H_INCLUDE 

#include "IPartition.h"
namespace hpgc{

	class IPartitionFactory
	{
	public:
		virtual IPartition * Create(int argc, char ** argv) = 0;
	};

}

#endif