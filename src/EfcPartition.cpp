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
    // because push_back last feaure
    int efc_index = m_efc - 1;
    OGRFeature * current = NULL;
	int id = 0;
    while (true) {
        current = srcLayer->GetNextFeature();
        if (current == NULL && srcFeatures.empty()) break;

        if (current!= NULL) {
            count++;
            srcFeatures.push_back(current->GetFID());
            if (count <= efc_index) {
                continue;
            }
            else{
                count = 0;
            }
        }
        cellar->AddBarrel(new VectorBarral(srcMeta->GetDataSourceName()
                                           , srcMeta->GetLayerName()
                                           , srcFeatures
                                           , dstMeta->GetDataSourceName()
                                           , dstMeta->GetLayerName()
										   , id ++)
                         );
        srcFeatures.clear();
    }
    return cellar;
}

hpgc::EfcPartition::EfcPartition(int index) {
    m_efc = index;
}

