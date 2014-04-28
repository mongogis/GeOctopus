#include "M2sScheduler.h"
#include <mpiobject.h>
#include <mpimessage.datblock.h>
#include <mpimessage.h>
#include <mpioperator.recvmsg.h>
#include <mpioperator.sendmsg.h>

void hpgc::M2sScheduler::Work()
{
}

void hpgc::M2sScheduler::SetRole(IRole * role)
{
	m_role = role;
}

void hpgc::M2sScheduler::SetCellar(VectorCellar * cellar)
{
	m_cellar = cellar;
}

int hpgc::M2sScheduler::Run(VectorBarral * barral)
{
	m_role->Action();
}

int hpgc::M2sScheduler::Stop(VectorBarral * barral)
{
	return 1;
}

int hpgc::M2sScheduler::Start(VectorBarral * barral)
{
	MPIObject mo;

	if (mo.GetOurSize() == 1)
	{
		return 1;
	}

	return Run(barral);
}
