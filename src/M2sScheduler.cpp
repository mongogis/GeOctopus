#include "M2sScheduler.h"
#include "mpiobject/mpiobject.h"

void hpgc::M2sScheduler::Work(VectorCellar * data, std::list<Role> roles, IV2VAlgorithm * compute)
{
	MPIObject mo;
	if (mo.IsMaster())
	{
	} 
	else
	{
	}
}
