#ifndef MasterRole_h__
#define MasterRole_h__

#include "IRole.h"
#include "IVectorScheduler.h"

namespace hpgc{
	class MasterRole:public IRole
	{
	public:
		virtual int Action();
		MasterRole(IVectorScheduler * schedular);

	private:
		IVectorScheduler * m_schedular;
	};
}
#endif // MasterRole_h__
