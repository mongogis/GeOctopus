#ifndef HPGC_ALGORITHM_H_INCLUDE

#define HPGC_ALGORITHM_H_INCLUDE

#include "IAlgorithm.h"
#include "IGeoAlgorithm.h"
#include "IPartition.h"
#include "IScheduler.h"

namespace hpgc{

	class HpgcAlgorithm : public IAlgorithm
	{
	public:
		HpgcAlgorithm(IGeoAlgorithm * geoalgorithm,IPartition * partition, IScheduler * scheduler);
		virtual bool Run();
		virtual void PreAlg();

	private:
		IGeoAlgorithm * m_geoAlgorithm;
		IPartition * m_partition;
		IScheduler * m_scheduler;

	};
}

#endif