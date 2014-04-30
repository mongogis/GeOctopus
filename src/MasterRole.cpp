#include "MasterRole.h"
#include <mpiobject.h>
#include <mpimessage.h>

int hpgc::MasterRole::Action()
{
	return 1;
}

hpgc::MasterRole::MasterRole(VectorCellar * cellar)
{
	m_cellar = cellar;
}
