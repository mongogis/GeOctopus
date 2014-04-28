#include "MasterRole.h"
#include <mpiobject.h>

int hpgc::MasterRole::Action()
{
	MPIObject mo;
	mo.PrintMe("I'm master");
	return 1;
}
