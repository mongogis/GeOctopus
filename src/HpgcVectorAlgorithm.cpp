#include "HpgcVectorAlgorithm.h"

hpgc::HpgcVectorAlgorithm::HpgcVectorAlgorithm(IV2VAlgorithm * alg, IVectorScheduler * she, IVectorPartition * par,VectorMetaData *meta)
{
	m_algorithm = alg;
	m_partition = par;
	m_scheduler = she;
	m_metaData = meta;
}

void hpgc::HpgcVectorAlgorithm::Run()
{
	VectorCellar * barral =  m_partition->Partition(m_metaData);
	m_scheduler->Work();
}
