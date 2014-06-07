#ifndef SlaveRole_h__
#define SlaveRole_h__

#include "IRole.h"
#include "IV2VAlgorithm.h"
#include "vector.metadata.h"
#include "rpc.h"
#include "rpc.message.pb.h"

namespace hpgc {
    class SlaveRole : public IRole {
    public:
        virtual int Action();
        SlaveRole(IV2VAlgorithm * task, MetaData * dst);
		~SlaveRole();
		int Id();
    private:
		bool m_workRunning;
		bool m_taskRunning;
        IV2VAlgorithm * m_alg;
        MetaData * m_dst;
		RPCNetwork * m_net;

		void HandleGameOver(const EmptyMessage & req,EmptyMessage * resp ,const RPCInfo& rpc );
    };
}
#endif // SlaveRole_h__
