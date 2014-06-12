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

	if (net->Id() == 0)
	{
		auto srcds = VectorOpen(pszSrcFile, GA_ReadOnly);
		auto dstds = VectorOpen(pszDstFile, GA_Update);

		auto srclayer = srcds->GetLayerByName(pszSrcLayer);
		auto dstlayer = dstds->CreateLayer(pszDstLayer,srs, wkbPolygon, pszlist);

		CopyLayerDefine(srclayer, dstlayer);

		VectorClose(dstds);
		VectorClose(srcds);
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

		// test celler to protobuf

		BUG("TEST PROTOBUF");

		auto barrel = celler->GetByIndex(1);
		BUG(celler->size());
		BUG(barrel->GetDstDataSource());

		DataMessage * data = DataMessageFromBarral(barrel);

		BUG(data->dstdatasource());
		BUG(data->srcdatasource());
		BUG(data->dstlayer());
		BUG(data->srclayer());

		std::string str = data->SerializeAsString();

		DataMessage data1;
		data1.ParseFromString(str);


		auto barreltest = BarralFromDataMessage(&data1);

		BUG(barreltest->GetDstDataSource());
		BUG(barreltest->GetSrcDataSource());
		BUG(barreltest->GetDstLayer());
		BUG(barreltest->GetSrcLayer());


		BUG("+++check+++");

		if (barreltest->GetDstDataSource() == data->dstdatasource())
		{
			BUG("dst ds OK");
		}
		else
		{
			BUG("!! dst ds WRONG");
		}

		if (barreltest->GetDstLayer() == data->dstlayer())
		{
			BUG("dst layer OK");
		}
		else
		{
			BUG("!! dst layer WRONG") ;
		}

		if (barreltest->GetSrcDataSource() == data->srcdatasource())
		{
			BUG("src ds OK");
		}
		else
		{
			BUG("!! src datasource WRONG");
		}

		if (barreltest->GetSrcLayer() == data->srclayer())
		{
			BUG("src layer OK");
		}
		else
		{
			BUG("!! src layer WRONG");
		}

		if (barreltest->Id() == data->dataindex())
		{
			BUG("id OK");
		}
		else
		{
			BUG("!!id WRONG");
		}
    }

    auto scheduler = new M2sScheduler();

    return 0;
    auto vct = new V2vProj(argc, argv);
    auto alg = new HpgcVectorAlgorithm(vct, scheduler, partition, metadata);
    alg->Run();
    return 0;
}
