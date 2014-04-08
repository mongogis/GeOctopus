#include "VectorBarrel.h"


std::string hpgc::VectorBarral::GetDataSource()
{
	return m_datasource;
}

std::string hpgc::VectorBarral::GetLayer()
{
	return m_layer;
}

std::list<int> hpgc::VectorBarral::GetFeatures()
{
	return m_features;
}
