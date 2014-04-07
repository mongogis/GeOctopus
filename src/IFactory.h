#ifndef HGPC_ABSTRACT_FACTORY_H_INCLUDE

#define HGPC_ABSTRACT_FACTORY_H_INCLUDE 

#include "IFactory.h"
#include "IScheduler.h"
#include "IPartition.h"
#include "HpgcAlgorithm.h"

namespace hpgc{

	class IFactory 
	{
	public:
		virtual const char * GetName() = 0;
		virtual const char * GetDescription()=0;
	};

	class ISchedulerFactory:public IFactory
	{
	public:
		virtual IScheduler  * Create() = 0;
	};

	class IGeoAlgFactory:public IFactory
	{
	public:
		virtual IGeoAlgorithm  * Create(int argc, char ** argv) = 0;
		//virtual IGeoAlgFactory()=0;
	};

	class IPartitionFactory:public IFactory
	{
	public:
		virtual IPartition * Create() = 0;
	};

}

#endif