#ifndef HPGC_ALGORITHM_H_INCLUDE

#define HPGC_ALGORITHM_H_INCLUDE 
#include "IPartition.h"
#include "IScheduler.h"
#include "IData.h"

namespace hpgc { 

class IGeoAlgorithm
{
public:
	virtual Barrel * GetBarrel()=0;
	virtual void SetBarrel(Barrel*)=0;
	virtual bool Computing() = 0;
	virtual void init(int argc, char ** argv)=0;
	virtual void help()=0;
};

class HpgcAlgorithm
{
private:
	IPartition *m_Partition;
	IScheduler *m_Scheduler;
	IGeoAlgorithm *m_GeoAlgorithm;
	Cellar * m_Cellar;

public:
	HpgcAlgorithm();

	IPartition *GetPartition();
	void SetPartition(IPartition *);

	IScheduler *GetScheduler();
	void SetScheduler(IScheduler *);

	IGeoAlgorithm *GetGeoAlgorithm();
	void SetGeoAlgorithm(IGeoAlgorithm *);

	virtual bool Run();
};


}

#endif