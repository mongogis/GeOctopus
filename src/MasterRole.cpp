#include "MasterRole.h"
#include <mpiobject.h>

int hpgc::MasterRole::Action()
{
	MPIObject mo;
	mo.PrintMe("I'm master");
	return 1;
}

hpgc::MasterRole::MasterRole(IVectorScheduler * schedular)
{
	m_schedular = schedular;
}
