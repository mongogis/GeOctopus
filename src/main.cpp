#include "HpgcVectorAlgorithm.h"
#include "v2vproj.h"
#include "EfcPartition.h"
#include "vector.metadata.h"
#include "M2sScheduler.h"
#include "port.debug.h"
#include "common.h"
#include "rpc.h"

#include <geoalgorithm.format.h>
#include <glog/logging.h>

using namespace hpgc;

int main(int argc, char ** argv) {
    HPGCInit(argc, argv);
    const char * pszSrcFile = "/home/huangtao/hpgc_new/test";
    const char * pszDstFile = "PG:dbname=postgis host=localhost port=5432 user=postgres password=postgres";
    const char * pszSrcLayer = "test";
    const char * pszDstLayer = "test";

	auto net = RPCNetwork::Get();
	
    char ** pszlist = NULL;
    pszlist = CSLAddString(pszlist,"OVERWRITE=YES");
    auto srs = (OGRSpatialReference *)OSRNewSpatialReference(NULL);
    srs->SetFromUserInput("EPSG:4326");
    BUG(srs);

	if (net->id() == 0)
	{
		auto ds = VectorOpen(pszDstFile, GA_Update);
        BUG(ds);
		auto layer = ds->CreateLayer(pszDstLayer,srs, wkbPolygon, pszlist);
        BUG(layer);
		VectorClose(ds);
	}

    auto metadata = new VectorMetaData(pszSrcFile, pszSrcLayer, pszDstFile,pszDstLayer);

    BUG(metadata->GetSrcMetaData()->GetDataSourceName());
    BUG(metadata->GetSrcMetaData()->GetLayerName());
    BUG(metadata->GetDstMetaData()->GetDataSourceName());
    BUG(metadata->GetDstMetaData()->GetLayerName());

    auto partition = new EfcPartition(2);

    auto celler = partition->Partition(metadata);

    for (int i = 0; i < celler->size(); ++i)
    {
        auto barrel = celler->GetByIndex(i);
        auto ls = barrel->GetFeatures();
        std::for_each(std::begin(ls),std::end(ls),[&](int x){BUG(x);});
        BUG("========");
    }

    auto scheduler = new M2sScheduler();

    return 0;
    auto vct = new V2vProj(argc, argv);
    auto alg = new HpgcVectorAlgorithm(vct, scheduler, partition, metadata);
    alg->Run();
    return 0;
}
