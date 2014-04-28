#ifndef M2sScheduler_h__
#define M2sScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc{

	class M2sScheduler: public IVectorScheduler
	{
	public:
		virtual void Work();
		virtual void SetRole(IRole * role);
		virtual void SetCellar(VectorCellar * cellar);
		virtual int Run(VectorBarral * barral);
		virtual int Stop(VectorBarral * barral);
		virtual int Start(VectorBarral * barral);
	private:
		IRole * m_role;
		VectorCellar * m_cellar;
	};

}

#endif // M2sScheduler_h__
