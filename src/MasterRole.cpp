#include "MasterRole.h"
#include <mpiobject.h>

int hpgc::MasterRole::Action()
{
	MPIObject mo;
	mo.PrintMe("wo are master");
	return 1;
}
