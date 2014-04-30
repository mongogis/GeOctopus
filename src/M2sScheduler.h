#ifndef M2sScheduler_h__
#define M2sScheduler_h__

#include "IVectorScheduler.h"
#include "HpgcVectorAlgorithm.h"

namespace hpgc{

	class M2sScheduler: public IVectorScheduler
	{
	public:
		virtual void Work(IV2VAlgorithm * task, HpgcVectorAlgorithm * hpgcAlg);
	};

}

#endif // M2sScheduler_h__
