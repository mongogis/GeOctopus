#include "v2vproj.h"
#include "geoalgorithm.format.h"
#include "ScopeGuard.h"
#include <algorithm>

namespace hpgc {

    V2vProj::V2vProj(int argc, char ** argv) {
        for (int i = 1; i < argc; i++) {
            if (EQUAL(argv[i], "-t")) {
                m_dst = argv[++i];
            }
            else if (EQUAL(argv[i], "-t_srs")) {
                m_srs = argv[++i];
            }
        }
        m_ogrSr = (OGRSpatialReference *)OSRNewSpatialReference(NULL);
        m_ogrSr->SetFromUserInput(m_srs);
    }

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
        std::for_each(begin(barrel->GetFeatures()), end(barrel->GetFeatures())
        , [&](int fid) {
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

}
