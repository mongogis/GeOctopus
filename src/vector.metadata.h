#ifndef vector_metadata_h__
#define vector_metadata_h__

namespace hpgc{

	class VectorMetaData
	{
	public:
		VectorMetaData(const char * src,const char * dst)
			:m_src(src)
			,m_dst(dst){
		};
		const char * GetSrcName();
		const char * GetDstName();
		~VectorMetaData();
	private:
		const char * m_src;
		const char * m_dst;
	};

}

#endif // vector.metadata_h__
