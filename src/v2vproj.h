#ifndef v2vproj_h__
#define v2vproj_h__

#include "IV2VAlgorithm.h"
#include <geoalgorithm.format.h>

namespace hpgc {
    class V2vProj : public IV2VAlgorithm {
    public:
        virtual bool Compute(VectorBarral * barrel);
        V2vProj(int argc, char ** argv);

    private:
        const char * m_srs ;
        OGRSpatialReference * m_ogrSr;
    };
}


#endif // v2vproj_h__
