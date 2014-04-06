#ifndef HPGC_INTERFACE_PARTITION_H_INCLUDE

#define HPGC_INTERFACE_PARTITION_H_INCLUDE

#include "ICellar.h"

namespace hpgc{

	class IPartition
	{
	public:
		virtual ICellar * Partitioning() = 0;
	};

}

#endif