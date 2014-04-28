#include "vector.metadata.h"

hpgc::VectorMetaData::~VectorMetaData()
{

}

const char * hpgc::VectorMetaData::GetSrcName()
{
	return m_src;
}

const char * hpgc::VectorMetaData::GetDstName()
{
	return m_dst;
}
