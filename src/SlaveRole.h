#ifndef SlaveRole_h__
#define SlaveRole_h__

#include "IRole.h"
#include "IV2VAlgorithm.h"
#include "vector.metadata.h"

namespace hpgc {
    class SlaveRole : public IRole {
    public:
        virtual int Action();
        SlaveRole(IV2VAlgorithm * task, MetaData * dst);
    private:
        IV2VAlgorithm * m_alg;
        MetaData * m_dst;
    };
}
#endif // SlaveRole_h__
