#include "EfcPartition.h"
#include "geoalgorithm.format.h"
#include "ScopeGuard.h"
#include <algorithm>
#include <string>

hpgc::VectorCellar * hpgc::EfcPartition::Partition(VectorMetaData * meta) {
    auto srcMeta = meta->GetSrcMetaData();
    auto srcDs = VectorOpen(srcMeta->GetDataSourceName(), GA_ReadOnly);
    ON_SCOPE_EXIT([&srcDs]() {OGRDataSource::DestroyDataSource(srcDs); });
    auto dstMeta = meta->GetDstMetaData();
    auto srcLayer = srcDs->GetLayerByName(srcMeta->GetLayerName());
    std::list<int> srcFeatures;
    auto cellar = new VectorCellar();
    int count = 0;
    int efc_index = m_efc;
    OGRFeature * current = NULL;
    while (true) {
        count++;
        if (count <= efc_index) {
            current = srcLayer->GetNextFeature();
            if (current != NULL) {
                srcFeatures.push_back(current->GetFID());
                continue;
            }
        }
        cellar->AddBarrel(new VectorBarral(srcMeta->GetDataSourceName()
                                           , srcMeta->GetLayerName()
                                           , srcFeatures
                                           , dstMeta->GetDataSourceName()
                                           , dstMeta->GetLayerName())
                         );
        srcFeatures.clear();
        count = 0;
        if (current == NULL) {
            break;
        }
        else {
            current = NULL;
        }
    }
    return cellar;
}

hpgc::EfcPartition::EfcPartition(int index) {
    m_efc = index;
}

