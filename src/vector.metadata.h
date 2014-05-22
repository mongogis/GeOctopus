#ifndef vector_metadata_h__
#define vector_metadata_h__

namespace hpgc {

    class MetaData {
    public:
        MetaData(const char * ds, const char * layer);
        const char * GetDataSourceName();
        const char * GetLayerName();
    private:
        const char * m_dataSource;
        const char * m_layer;
    };

    class VectorMetaData {
    public:
        VectorMetaData(const char * srcds, const char * srclayer, const char * dstds,
                       const char * dstlayer);
        MetaData * GetSrcMetaData();
        MetaData * GetDstMetaData();
        ~VectorMetaData();
    private:
        MetaData * m_src;
        MetaData * m_dst;
    };

}

#endif // vector.metadata_h__
