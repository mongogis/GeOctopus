#ifndef V2VAlgorithm_h__
#define V2VAlgorithm_h__

#include "VectorBarrel.h"

namespace hpgc {
    class IV2VAlgorithm {
    public:
        virtual bool Compute(VectorBarral * barrel) = 0;
    };
}

#endif // V2VAlgorithm_h__
