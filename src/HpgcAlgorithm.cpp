// 实现hpgcAlgorithm相关
#include "HpgcAlgorithm.h"
#include <stdio.h>

bool hpgc::HpgcAlgorithm::Run()
{
	printf("This is IHpgcAlgorithm::Run()!");
	return 1;
};

hpgc::HpgcAlgorithm::HpgcAlgorithm()
{

};

hpgc::IPartition *hpgc::HpgcAlgorithm::GetPartition()
{
	return NULL;
};
void hpgc::HpgcAlgorithm::SetPartition(IPartition *)
{

};

hpgc::IScheduler *hpgc::HpgcAlgorithm::GetScheduler()
{
	return NULL;
};
void hpgc::HpgcAlgorithm::SetScheduler(IScheduler *)
{

};

hpgc::IGeoAlgorithm *hpgc::HpgcAlgorithm::GetGeoAlgorithm()
{
	return NULL;
};
void hpgc::HpgcAlgorithm::SetGeoAlgorithm(IGeoAlgorithm *)
{

};