#ifndef MasterRole_h__
#define MasterRole_h__

#include "IRole.h"

namespace hpgc{
	class MasterRole:public IRole
	{
	public:
		virtual int Action();
	};
}
#endif // MasterRole_h__
