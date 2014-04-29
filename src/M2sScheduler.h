#ifndef M2sScheduler_h__
#define M2sScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc{

	class M2sScheduler: public IVectorScheduler
	{
	public:
		virtual void Work(IV2VAlgorithm * alg);
		virtual void SetRole(IRole * role);
		virtual void SetCellar(VectorCellar * cellar);
		virtual IRole * GetRole();
		virtual VectorCellar * GetCellar();
	private:
		IRole * m_role;
		VectorCellar * m_cellar;
		IV2VAlgorithm * m_alg;
	};

}

#endif // M2sScheduler_h__
