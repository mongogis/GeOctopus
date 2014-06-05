#ifndef MasterRole_h__
#define MasterRole_h__

#include "IRole.h"
#include "IVectorScheduler.h"
#include <queue>
#include "MessageTag.h"
#include <mpiobject.h>

namespace hpgc {
    class MasterRole: public IRole {
    public:
        virtual int Action();
        MasterRole(VectorCellar * cellar);


    private:
        void ReadyToGo();
        void SendFirstBarrel();
        TaskInfo * ReceiveSlaveMsg();
        void SendNoData(int process);
        void SendData(DataInfo & data, int process);
        bool IsAllSlaveOver();

        VectorCellar * m_cellar;
        std::queue<int> m_cellarIndex;
        std::queue<int> m_activeSlaves;
        std::queue<int> m_sleepSlaves;
        MPIObject m_mpi;
    };
}
#endif // MasterRole_h__
