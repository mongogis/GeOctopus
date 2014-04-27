#ifndef M2sScheduler_h__
#define M2sScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc{

	class M2sScheduler: public IVectorScheduler
	{
	public:
		virtual void Work();
		virtual void SetMaster(IRole * master);
		virtual void SetSlave(IRole * slave);
		virtual void SetCellar(VectorCellar * cellar);
	private:
		IRole * m_master;
		IRole * m_slave;
		VectorCellar * m_cellar;
	};

}

#endif // M2sScheduler_h__
