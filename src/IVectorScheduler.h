#ifndef HPGC_INTERFACE_SCHEDULER_H_INCLUDE

#define HPGC_INTERFACE_SCHEDULER_H_INCLUDE 

#include "Role.h"
#include "IV2VAlgorithm.h"
#include "VectorCellar.h"

#include <list>

namespace hpgc{

	class IVectorScheduler
	{
	public:
		virtual void Work(VectorCellar * data,std::list<Role> roles,IV2VAlgorithm * compute) = 0;	
	};

}

#endif 
