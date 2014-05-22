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

#include <mpiobject.h>
#include <geoalgorithm.format.h>
#include "port.debug.h"

using namespace hpgc;

int main(int argc, char ** argv) {
    MPIObject::CreateMPI(argc, argv);
    RegisterVector();
    MPIObject mo;
    const char * pszSrcFile = NULL;
    const char * pszDstFile = NULL;
    const char * pszSrcLayer = NULL;
    const char * pszDstLayer = NULL;
    for (int i = 1; i < argc; i++) {
        if (EQUAL(argv[i], "-s") && i < argc - 1) {
            pszSrcFile = argv[++i];
        }
        else if (EQUAL(argv[i], "-d") && i < argc - 1) {
            pszDstFile = argv[++i];
        }
    }
    auto metadata = new VectorMetaData(pszSrcFile, pszSrcLayer, pszDstFile,
                                       pszDstLayer);
    auto partition = new EfcPartition(2);
    auto scheduler = new M2sScheduler();
    auto vct = new V2vProj(pszDstFile, "");
    auto alg = new HpgcVectorAlgorithm(vct, scheduler, partition, metadata);
    alg->Run();
    MPIObject::DestoryMPI();
    return 0;
}