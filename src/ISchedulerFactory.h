#ifndef HPGC_INTERFACE_SCHEDULER_FACTORY_H_INCLUDE

#define HPGC_INTERFACE_SCHEDULER_FACTORY_H_INCLUDE

#include "IScheduler.h"

namespace hpgc{

	class ISchedulerFactory
	{
	public:
		virtual IScheduler * Create(int argc, char ** argv) = 0;
	};

}

#endif