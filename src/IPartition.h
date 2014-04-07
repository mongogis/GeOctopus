#ifndef HPGC_INTERFACE_PARTITION_H_INCLUDE

#define HPGC_INTERFACE_PARTITION_H_INCLUDE

#include "IData.h"

namespace hpgc{

	class IPartition
	{
	public:
		virtual MetaData * GetMetaData()=0;
		virtual Cellar * Partitioning() = 0;
	};

	class EFC_Partition:public IPartition
	{
	public:
		MetaData * GetMetaData();
		Cellar * Partitioning();
	};
	class FCI_Partition:public IPartition
	{
	public:
		MetaData * GetMetaData();
		Cellar * Partitioning();
	};
}

#endif