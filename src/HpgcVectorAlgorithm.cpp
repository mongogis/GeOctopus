#include "HpgcVectorAlgorithm.h"
#include "MasterRole.h"
#include "SlaveRole.h"
#include <mpiobject.h>

hpgc::HpgcVectorAlgorithm::HpgcVectorAlgorithm(IV2VAlgorithm * alg, IVectorScheduler * she, IVectorPartition * par,VectorMetaData *meta)
{
	m_algorithm = alg;
	m_partition = par;
	m_scheduler = she;
	m_metaData = meta;
}

void hpgc::HpgcVectorAlgorithm::Run()
{
	MPIObject mo;

	if (mo.IsMaster())
	{
		VectorCellar * cellar =  m_partition->Partition(m_metaData);
		IRole * master = new MasterRole();
		m_scheduler->SetRole(master);
		m_scheduler->SetCellar(cellar);
	}
	else
	{
		IRole * slave = new SlaveRole();
		m_scheduler->SetRole(slave);
		m_scheduler->SetCellar(NULL);
	}

	// 目的数据没有说明，这里要考虑
	VectorBarral * src = new VectorBarral();
	for (int algStatus = m_scheduler->Start(src);
		algStatus != m_scheduler->Stop(src);
		algStatus = m_scheduler->Run(src));
	{
		m_algorithm->Compute(src,src);
	}
}
