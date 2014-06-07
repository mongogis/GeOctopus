#ifndef MasterRole_h__
#define MasterRole_h__

#include "IRole.h"
#include "IVectorScheduler.h"
#include "rpc.h"

#include <queue>
#include <map>

namespace hpgc {

	struct TaskState;
	struct Taskid;

    class MasterRole: public IRole {
    public:
        virtual int Action();
        MasterRole(VectorCellar * cellar);
		~MasterRole();

    private:
		bool m_masterRuning;
		std::queue<int> m_activeSlaves;
		std::vector<Record * > m_statistics;
		RPCNetwork * m_net;
    };
}
#endif // MasterRole_h__
