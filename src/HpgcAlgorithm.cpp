#include "HpgcAlgorithm.h"

hpgc::HpgcAlgorithm::HpgcAlgorithm(IGeoAlgorithm * geoalgorithm, IPartition * partition, IScheduler * scheduler)
{
	this->m_geoAlgorithm = geoalgorithm;
	this->m_partition = partition;
	this->m_scheduler = m_scheduler;
}

bool hpgc::HpgcAlgorithm::Run()
{
		
}


