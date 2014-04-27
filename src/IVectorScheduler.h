#ifndef HPGC_INTERFACE_SCHEDULER_H_INCLUDE

#define HPGC_INTERFACE_SCHEDULER_H_INCLUDE 

#include "IRole.h"
#include "IV2VAlgorithm.h"
#include "VectorCellar.h"

#include <list>

namespace hpgc{

	class IVectorScheduler
	{
	public:
		virtual void Work() = 0;	
	};

}

#endif 
