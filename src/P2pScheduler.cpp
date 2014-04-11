#include "P2pScheduler.h"

hpgc::VectorCellar * hpgc::P2pScheduler::Work(VectorCellar * data, std::list<Role> roles, IV2VAlgorithm * compute)
{
	int worker_count = m_roles.size();
	int task_count = m_celler->size();
	int chunk_size = task_count / worker_count;
}

hpgc::P2pScheduler::P2pScheduler(VectorCellar * data, std::list<Role> role, IV2VAlgorithm * alg)
{
	this->m_celler = data;
	this->m_roles = role;
	this->m_algorithm = alg;
}
