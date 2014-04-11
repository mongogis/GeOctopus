#ifndef P2pScheduler_h__
#define P2pScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc{
	class P2pScheduler:public IVectorScheduler
	{
	public:
		virtual VectorCellar * Work(VectorCellar * data, std::list<Role> roles, IV2VAlgorithm * compute);
		P2pScheduler(VectorCellar * data, std::list<Role> role, IV2VAlgorithm * alg);

	private:
		VectorCellar * m_celler;
		std::list<Role> m_roles;
		IV2VAlgorithm * m_algorithm;
	};

}
#endif // P2pScheduler_h__
