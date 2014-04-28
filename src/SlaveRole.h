#ifndef SlaveRole_h__
#define SlaveRole_h__

#include "IRole.h"

namespace hpgc{
	class SlaveRole : public IRole
	{
	public:
		virtual int Action();
	};
}
#endif // SlaveRole_h__
