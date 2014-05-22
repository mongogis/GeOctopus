#ifndef v2vproj_h__
#define v2vproj_h__

#include "IV2VAlgorithm.h"
#include <geoalgorithm.format.h>

namespace hpgc {
    class V2vProj : public IV2VAlgorithm {
    public:
        virtual bool Compute(VectorBarral * barrel);
        V2vProj(const char * dst, const char * srs);

    private:
        const char * m_dst;
        const char * m_srs;
        OGRSpatialReference * m_ogrSr;
    };
}


#endif // v2vproj_h__
