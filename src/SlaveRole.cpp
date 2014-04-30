#include "SlaveRole.h"
#include <mpiobject.h>
#include <mpimessage.h>
#include <mpioperator.sendmsg.h>

int hpgc::SlaveRole::Action() {
    MPIObject mo;
    int num = mo.GetRank();
    MPIMessage sMsg(&num, 1, MPI_INT, mo.GetMaster(), 1, mo.GetComm());
    SendMsg(sMsg);
    VectorBarral * barral = NULL;
    m_alg->Compute(barral);
    return 1;
}

hpgc::SlaveRole::SlaveRole(IV2VAlgorithm * task, MetaData * dst) {
    m_alg = task;
    m_dst = dst;
}
