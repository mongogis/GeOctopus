#include "M2sScheduler.h"
#include <mpiobject.h>

#include "MasterRole.h"
#include "SlaveRole.h"

void hpgc::M2sScheduler::SetRole(IRole * role)
{
	m_role = role;
}

void hpgc::M2sScheduler::SetCellar(VectorCellar * cellar)
{
	m_cellar = cellar;
}

void hpgc::M2sScheduler::Work(IV2VAlgorithm * task, HpgcVectorAlgorithm * hpgcAlg)
{
	MPIObject mo;

	if (mo.IsMaster())
	{
		auto meta = hpgcAlg->GetMetaData();
		auto partition = hpgcAlg->GetPartition();
		VectorCellar * cellar =partition->Partition(meta);
		IRole * master = new MasterRole(this);
		this->SetRole(master);
		this->SetCellar(cellar);
	}
	else
	{
		IRole * slave = new SlaveRole(task);
		this->SetRole(slave);
		this->SetCellar(NULL);
	}

	m_role->Action();
}

hpgc::IRole * hpgc::M2sScheduler::GetRole()
{
	return m_role;
}

hpgc::VectorCellar * hpgc::M2sScheduler::GetCellar()
{
	return m_cellar;
}


