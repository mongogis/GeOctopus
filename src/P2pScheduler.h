#ifndef P2pScheduler_h__
#define P2pScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc {
    class P2pScheduler: public IVectorScheduler {
    public:
        virtual void Work(VectorCellar * data, std::list<IRole> roles,
                          IV2VAlgorithm * compute);
        P2pScheduler(VectorCellar * data, std::list<IRole> role, IV2VAlgorithm * alg);

    private:
        VectorCellar * m_celler;
        std::list<IRole> m_roles;
        IV2VAlgorithm * m_algorithm;
    };

}
#endif // P2pScheduler_h__
