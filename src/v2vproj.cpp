#include "v2vproj.h"
#include "geoalgorithm.format.h"
#include "ScopeGuard.h"
#include <algorithm>


namespace hpgc {

    bool V2vProj::Compute(VectorBarral * barrel) {
        OGRDataSource * poSourceDs = VectorOpen(barrel->GetSrcDataSource().c_str(),
                                                GA_ReadOnly);
        ON_SCOPE_EXIT([&]() {OGRDataSource::DestroyDataSource(poSourceDs); });
        OGRDataSource * poOutputDs = VectorOpen(barrel->GetDstDataSource().c_str(),
                                                GA_Update);
        ON_SCOPE_EXIT([&]() {OGRDataSource::DestroyDataSource(poOutputDs); });
        OGRLayer * poSrcLayer = poSourceDs->GetLayerByName(
                                    barrel->GetSrcLayer().c_str());
        OGRLayer * poDstLayer = poOutputDs->GetLayerByName(
                                    barrel->GetDstLayer().c_str());
        OGRSpatialReference * poSourceSRS = poSrcLayer->GetSpatialRef();
        OGRCoordinateTransformation * poCT = poCT = OGRCreateCoordinateTransformation(
                poSourceSRS, m_ogrSr);
        OGRFeatureDefn * poDstFeatureDefn = poDstLayer->GetLayerDefn();
        std::for_each(begin(barrel->GetFeatures()),
        end(barrel->GetFeatures()), [&](int fid) {
            OGRFeature * poDstFeature = OGRFeature::CreateFeature(poDstFeatureDefn);
            ON_SCOPE_EXIT([&]() {OGRFeature::DestroyFeature(poDstFeature); });
            poDstFeature->SetFrom(poSrcLayer->GetFeature(fid));
            OGRGeometry * poDstGeometry = poDstFeature->GetGeometryRef();
            OGRGeometry * poReprojectedGeom = OGRGeometryFactory::transformWithOptions(
                                                  poDstGeometry, poCT, NULL);
            poDstFeature->SetGeometryDirectly(poReprojectedGeom);
            poDstLayer->CreateFeature(poDstFeature);
        });
        return true;
    }

    V2vProj::V2vProj(const char * dst, const char * srs) : m_dst(dst), m_srs(srs) {
        m_ogrSr = (OGRSpatialReference *)OSRNewSpatialReference(NULL);
        m_ogrSr->SetFromUserInput(m_srs);
    }

}
