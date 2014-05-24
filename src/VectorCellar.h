#ifndef HPGCH_VECTOR_CELLAR_H_INCLUDE

#define HPGCH_VECTOR_CELLAR_H_INCLUDE

#include "VectorBarrel.h"

#include <vector>

namespace hpgc {

    class VectorCellar {
    public:
        virtual void AddBarrel(VectorBarral * barrel) ;

        virtual VectorBarral * GetByIndex(int index) ;

        virtual bool IsEmpty() ;

        virtual int size();

        ~VectorCellar();

    private:
        std::vector<VectorBarral * > m_barrels;
    };
}

#endif