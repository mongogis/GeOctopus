#ifndef HpgcVectorAlgorithm_h__
#define HpgcVectorAlgorithm_h__

#include "IV2VAlgorithm.h"
#include "IVectorPartition.h"
#include "IVectorScheduler.h"

namespace hpgc{

	class HpgcVectorAlgorithm
	{

	public:
		HpgcVectorAlgorithm(IV2VAlgorithm * alg, IVectorScheduler * she, IVectorPartition * par,VectorMetaData * data);
		void Run();
	private:
		IV2VAlgorithm * m_algorithm;
		IVectorPartition * m_partition;
		IVectorScheduler * m_scheduler;
		VectorMetaData * m_metaData;
	};


}

#endif // HpgcVectorAlgorithm_h__
