<<<<<<< HEAD
#ifndef HPGC_ALGORITHM_H_INCLUDE

#define HPGC_ALGORITHM_H_INCLUDE

#include "IAlgorithm.h"
#include "IGeoAlgorithm.h"
#include "IPartition.h"
#include "ICellar.h"
#include "Process.h"
#include "IScheduler.h"

#include <list>

namespace hpgc{

	class HpgcAlgorithm : public IAlgorithm
	{
	public:
		HpgcAlgorithm(IGeoAlgorithm * geoalgorithm,IPartition * partition, IScheduler * scheduler);
		virtual void Run();
		virtual void PreAlg();

	private:
		IGeoAlgorithm * m_geoAlgorithm;
		IPartition * m_partition;
		IScheduler * m_scheduler;
		ICellar * m_cellar;
		std::list<Process> m_processes;
		
	};
}

=======
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

>>>>>>> ac83431c1fba32b970c1af616d29106c6bf92625
#endif