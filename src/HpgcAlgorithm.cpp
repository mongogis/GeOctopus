#include "HpgcAlgorithm.h"

hpgc::HpgcAlgorithm::HpgcAlgorithm(IGeoAlgorithm * geoalgorithm, IPartition * partition, IScheduler * scheduler)
{
	this->m_geoAlgorithm = geoalgorithm;
	this->m_partition = partition;
	this->m_scheduler = m_scheduler;
}

bool hpgc::HpgcAlgorithm::Run()
{
	PreAlg();
	m_scheduler->Work(m_cellar,m_processes);
}

void hpgc::HpgcAlgorithm::PreAlg()
{
	m_geoAlgorithm->Init();
	m_cellar = m_partition->Partitioning();
	m_processes = m_scheduler->InitProcess();
}



