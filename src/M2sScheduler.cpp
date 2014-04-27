#include "M2sScheduler.h"

void hpgc::M2sScheduler::Work()
{

}

void hpgc::M2sScheduler::SetMaster(IRole * master)
{
	m_master = master;
}

void hpgc::M2sScheduler::SetSlave(IRole * slave)
{
	m_slave = slave;
}

void hpgc::M2sScheduler::SetCellar(VectorCellar * cellar)
{
	m_cellar = cellar;
}
