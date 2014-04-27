#ifndef vector_metadata_h__
#define vector_metadata_h__

namespace hpgc{

	class VectorMetaData
	{
	public:
		VectorMetaData(int argc,char ** argv);
		const char * GetSrcName();
		const char * GetDstName();
		~VectorMetaData();
	private:
		char * m_src;
		char * m_dst;
	};

}

#endif // vector.metadata_h__
