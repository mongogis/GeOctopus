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
	

	if (net->id() == 0)
	{
		auto ds = VectorOpen(pszDstLayer, GA_Update);
		ds->CreateLayer(pszDstLayer, NULL, wkbUnknown, NULL);
		VectorClose(ds);
	}

	return 1;
	

    auto metadata = new VectorMetaData(pszSrcFile, pszSrcLayer, pszDstFile,
                                       pszDstLayer);
    auto partition = new EfcPartition(2);
    auto scheduler = new M2sScheduler();
    auto vct = new V2vProj(argc, argv);
    auto alg = new HpgcVectorAlgorithm(vct, scheduler, partition, metadata);
    alg->Run();
    return 0;
}
