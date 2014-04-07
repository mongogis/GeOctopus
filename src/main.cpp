#include "hpgc.h"
#include "port.h"

using namespace hpgc;

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

void main(int argc, char ** argv)
{
	char * pstrScheduler=NULL;
	hpgc::IScheduler* pScheduler=NULL;

	char * pstrPartition=NULL;
	hpgc::IPartition* pPartition=NULL;

	char * pstrGeoAlgorithm=NULL;
	IGeoAlgorithm * pGeoAlgorithm =NULL;

	for(int i = 1; i < argc; i++)
		if (EQUAL(argv[i], "-par") && i < argc - 1)
			if (pstrPartition==NULL)
				pstrPartition = argv[++i];	
			else if (EQUAL(argv[i], "-sch") && i < argc - 1)
				if(pstrScheduler==NULL)
					pstrScheduler = argv[++i];
			else if (EQUAL(argv[i], "-alg") && i < argc - 1)
				if (pstrGeoAlgorithm==NULL)
				{
					pstrGeoAlgorithm = argv[++i];
					if (pstrGeoAlgorithm==NULL || pstrGeoAlgorithm =="")
						continue;
					else
						break;
				}

	if (pstrGeoAlgorithm=NULL)
		exit(1);

	SchFactoryMan * pSchFactoryMan=SchFactoryMan::GetInstance();
	pScheduler=pSchFactoryMan->FindFactory(pstrScheduler)->Create();

	ParFactoryMan * pParFactoryMan=ParFactoryMan::GetInstance();
	pPartition=pParFactoryMan->FindFactory(pstrPartition)->Create();

	AlgFactoryMan * pAlgFactoryMan=AlgFactoryMan::GetInstance();
	pGeoAlgorithm=pAlgFactoryMan->FindFactory(pstrGeoAlgorithm)->Create(argc,argv);

	HpgcAlgorithm *pHpgcAlg=new HpgcAlgorithm();
	pHpgcAlg->SetScheduler(pScheduler);
	pHpgcAlg->SetPartition(pPartition);
	pHpgcAlg->SetGeoAlgorithm(pGeoAlgorithm);
	pHpgcAlg->Run();
}