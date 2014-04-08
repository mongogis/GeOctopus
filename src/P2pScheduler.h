#ifndef P2pScheduler_h__
#define P2pScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc{
	class P2pScheduler:public IVectorScheduler
	{
	public:
		virtual VectorCellar * Work(VectorCellar * data, std::list<Role> roles, IV2VAlgorithm * compute);
	};

}
#endif // P2pScheduler_h__
