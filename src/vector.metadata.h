#ifndef vector_metadata_h__
#define vector_metadata_h__

namespace hpgc{

	class MetaData
	{
	public:
		MetaData(const char * name);
		const char * GetDescription();
	private:
		const char * m_description;
	};

	class VectorMetaData
	{
	public:
		VectorMetaData(const char * src, const char * dst);
		MetaData * GetSrcMetaData();
		MetaData * GetDstMetaData();
		~VectorMetaData();
	private:
		MetaData * m_src;
		MetaData * m_dst;
	};

}

#endif // vector.metadata_h__
