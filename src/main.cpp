/// @brief 所有并行地理算法统一调用前端
///
/// -np 进程个数，-hostfile 计算节点信息，-alg 算法名称，
/// -par 划分策略，-sch 调度策略，[options...]其他算法参数。
///
/// @ref AlgFactoryMan处理-alg参数，@ref ParFactory处理-par参数，
/// @ref SchFactory处理-sch参数，@ref AlgFactory整合这些参数，
/// 算法的其余参数由算法本身解析处理
///
/// hpgc framework按照上述指定参数执行相应并行算法，
/// 如相应信息没有指定则使用默认值，参数有误则退出执行。

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
	

    auto metadata = new VectorMetaData(pszSrcFile, pszSrcLayer, pszDstFile,
                                       pszDstLayer);
    auto partition = new EfcPartition(2);
    auto scheduler = new M2sScheduler();
    auto vct = new V2vProj(argc, argv);
    auto alg = new HpgcVectorAlgorithm(vct, scheduler, partition, metadata);
    alg->Run();
    return 0;
}
