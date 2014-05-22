#ifndef HPGCH_VECTOR_BARREL_H_INCLUDE

#define HPGCH_VECTOR_BARREL_H_INCLUDE

#include <list>
#include <string>

namespace hpgc {

    class VectorBarral {

    public:

        std::string GetSrcDataSource();

        std::string GetSrcLayer();

        std::list<int> GetFeatures();

        std::string GetDstDataSource();

        std::string GetDstLayer();

        VectorBarral(std::string srcds, std::string srclayer, std::list<int> features,
                     std::string dstds, std::string dstlayer)
            : m_srcDatasource(srcds)
            , m_srcLayer(srclayer)
            , m_features(features)
            , m_dstDatasource(dstds)
            , m_dstLayer(dstlayer) {
        };

        VectorBarral() {};

    private:
        std::string m_srcDatasource;
        std::string m_srcLayer;
        std::list<int> m_features;
        std::string m_dstDatasource;
        std::string m_dstLayer;
    };

}

#endif