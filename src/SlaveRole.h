#ifndef SlaveRole_h__
#define SlaveRole_h__

#include "IRole.h"
#include "IV2VAlgorithm.h"
#include "vector.metadata.h"
#include <mpiobject.h>
#include "MessageTag.h"

namespace hpgc {
    class SlaveRole : public IRole {
    public:
        virtual int Action();
        SlaveRole(IV2VAlgorithm * task, MetaData * dst);
    private:
        void ReadyToGo();
        DataInfo * ReceiveMasterMsg();
        void SendTaskInfo(TaskInfo info);

        IV2VAlgorithm * m_alg;
        MetaData * m_dst;
        MPIObject m_mpi;
    };
}
#endif // SlaveRole_h__
