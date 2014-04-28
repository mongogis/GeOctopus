#include "M2sScheduler.h"

void hpgc::M2sScheduler::SetRole(IRole * role)
{
	m_role = role;
}

void hpgc::M2sScheduler::SetCellar(VectorCellar * cellar)
{
	m_cellar = cellar;
}

void hpgc::M2sScheduler::Work(IV2VAlgorithm * alg)
{
	m_role->Action();
}
