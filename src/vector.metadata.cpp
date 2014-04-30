#include "vector.metadata.h"

hpgc::VectorMetaData::~VectorMetaData()
{

}

hpgc::VectorMetaData::VectorMetaData(const char * src, const char * dst)
{
	m_src = new MetaData(src);
	m_dst = new MetaData(dst);
}

hpgc::MetaData * hpgc::VectorMetaData::GetSrcMetaData()
{
	return m_src;
}

hpgc::MetaData * hpgc::VectorMetaData::GetDstMetaData()
{
	return m_dst;
}

const char * hpgc::MetaData::GetDescription()
{
	return m_description;
}

hpgc::MetaData::MetaData(const char * name) 
	:m_description(name)
{

}
