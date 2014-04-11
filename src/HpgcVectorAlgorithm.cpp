#include "HpgcVectorAlgorithm.h"

hpgc::HpgcVectorAlgorithm::HpgcVectorAlgorithm(IV2VAlgorithm * alg, IVectorScheduler * she, IVectorPartition * par)
{
	m_algorithm = alg;
	m_partition = par;
	m_scheduler = she;

	
}

void hpgc::HpgcVectorAlgorithm::Run()
{

}
