#include "hpgc.h"
using namespace hpgc;

/// @brief 所有并行地理算法统一调用前端
///
/// -np 进程个数，-hostfile 计算节点信息，-alg 算法名称，
/// -par 划分策略，-sch 调度策略，[options...]其他算法参数。
///
/// @ref ServiceCenter处理-alg参数，@ref ParFactory处理-par参数，
/// @ref SchFactory处理-sch参数，@ref AlgFactory整合这些参数，
/// 算法的其余参数由算法本身解析处理
/// 
/// hpgc framework按照上述指定参数执行相应并行算法，
/// 如相应信息没有指定则使用默认值，参数有误则退出执行。
void main(int argc, char ** argv)
{
	AlgFactory * pfactory = ServiceCenter.Create(argc, argv);
	HpgcAlgorithm * palg = pfactory->Create(argc, argv);
	palg->Run();
}