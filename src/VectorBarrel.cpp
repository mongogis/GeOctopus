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

void hpgc::VectorBarral::SetDataSource(std::string datasource)
{
    m_datasource = datasource;
}

void hpgc::VectorBarral::SetLayer(std::string layer)
{
    m_layer = layer;
}

void hpgc::VectorBarral::SetFeatures(std::list<int> feats)
{
    m_features = feats;
}

