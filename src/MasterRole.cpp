#include "MasterRole.h"
#include <mpiobject.h>
#include <mpimessage.h>
#include <mpioperator.recvmsg.h>
#include "port.debug.h"
#include <geoalgorithm.format.h>

int hpgc::MasterRole::Action() {
    MPIObject mo;
    int num = -1;
    MPIMessage rMsg(&num, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, mo.GetComm());
    int size = mo.GetOurSize() - 1;
    for (int i = 0; i < size; ++i) {
        RecvMsg(rMsg);
        BUG(num);
    }
    return 1;
}


hpgc::MasterRole::MasterRole(VectorCellar * cellar) {
    m_cellar = cellar;
}
