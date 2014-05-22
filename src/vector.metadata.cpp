#include "vector.metadata.h"

hpgc::VectorMetaData::~VectorMetaData() {
}

hpgc::VectorMetaData::VectorMetaData(const char * srcds, const char * srclayer,
                                     const char * dstds, const char * dstlayer) {
    m_src = new MetaData(srcds, srclayer);
    m_dst = new MetaData(dstds, dstlayer);
}


hpgc::MetaData * hpgc::VectorMetaData::GetSrcMetaData() {
    return m_src;
}

hpgc::MetaData * hpgc::VectorMetaData::GetDstMetaData() {
    return m_dst;
}

const char * hpgc::MetaData::GetDataSourceName() {
    return m_dataSource;
}

hpgc::MetaData::MetaData(const char * ds, const char * layer)
    : m_dataSource(ds)
    , m_layer(layer) {
}

const char * hpgc::MetaData::GetLayerName() {
    return m_layer;
}
