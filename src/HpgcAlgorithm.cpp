#include "HpgcAlgorithm.h"

hpgc::HpgcAlgorithm::HpgcAlgorithm(IGeoAlgorithm * geoalgorithm, IPartition * partition, IScheduler * scheduler)
{
	this->m_geoAlgorithm = geoalgorithm;
	this->m_partition = partition;
	this->m_scheduler = m_scheduler;
}

bool hpgc::HpgcAlgorithm::Run()
{
	m_geoAlgorithm->Init();
	PreAlg();
	auto cellar = m_partition->Partitioning();
	m_scheduler->Start();
}

void hpgc::HpgcAlgorithm::PreAlg()
{

}



