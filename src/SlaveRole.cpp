#include "SlaveRole.h"
#include <mpiobject.h>
#include <mpimessage.h>

int hpgc::SlaveRole::Action()
{
	VectorBarral * barral;
	m_alg->Compute(barral);
	return 1;
}

hpgc::SlaveRole::SlaveRole(IV2VAlgorithm * task,MetaData * dst)
{
	m_alg = task;
	m_dst = dst;
}
