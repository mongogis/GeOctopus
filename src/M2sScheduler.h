#ifndef M2sScheduler_h__
#define M2sScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc{

	class M2sScheduler: public IVectorScheduler
	{
	public:
		virtual void Work(VectorCellar * data, std::list<Role> roles, IV2VAlgorithm * compute);
	};

}

#endif // M2sScheduler_h__
