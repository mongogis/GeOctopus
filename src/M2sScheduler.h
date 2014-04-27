#ifndef M2sScheduler_h__
#define M2sScheduler_h__

#include "IVectorScheduler.h"

namespace hpgc{

	class M2sScheduler: public IVectorScheduler
	{
	public:
		virtual void Work();
		void SetMaster(IRole * master);
		void SetSlave(IRole * slave);
		void SetCellar(VectorCellar * cellar);
	private:
		IRole * m_master;
		IRole * m_slave;
		VectorCellar * m_cellar;
	};

}

#endif // M2sScheduler_h__
