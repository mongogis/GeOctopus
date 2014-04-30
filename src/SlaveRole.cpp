#include "SlaveRole.h"
#include <mpiobject.h>

int hpgc::SlaveRole::Action()
{
	MPIObject mo;
	mo.PrintMe("we are slave");
	return 1;
}

hpgc::SlaveRole::SlaveRole(IV2VAlgorithm * task)
{
	m_alg = task;
}
