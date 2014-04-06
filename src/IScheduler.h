#ifndef HPGC_INTERFACE_SCHEDULER_H_INCLUDE

#define HPGC_INTERFACE_SCHEDULER_H_INCLUDE 

#include "ICellar.h"
#include "Process.h"

#include <list>

namespace hpgc{

	class IScheduler
	{
	public:
		virtual void Work(ICellar * data,std::list<Process> proes) = 0;
		virtual std::list<Process> InitProcess();
	};

}

#endif 
