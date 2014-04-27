#include "HpgcVectorAlgorithm.h"
#include "MasterRole.h"
#include "SlaveRole.h"

hpgc::HpgcVectorAlgorithm::HpgcVectorAlgorithm(IV2VAlgorithm * alg, IVectorScheduler * she, IVectorPartition * par,VectorMetaData *meta)
{
	m_algorithm = alg;
	m_partition = par;
	m_scheduler = she;
	m_metaData = meta;
}

void hpgc::HpgcVectorAlgorithm::Run()
{
	VectorCellar * cellar =  m_partition->Partition(m_metaData);

	IRole * master = new MasterRole();
	IRole * slave = new SlaveRole();

	m_scheduler->SetCellar(cellar);
	m_scheduler->SetMaster(master);
	m_scheduler->SetSlave(slave);

	m_scheduler->Work();
}
