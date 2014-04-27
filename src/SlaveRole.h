#ifndef SlaveRole_h__
#define SlaveRole_h__

#include "IRole.h"

namespace hpgc{
	class SlaveRole : public IRole
	{
	public:
		virtual int Action(VectorBarral * barral);
	};
}
#endif // SlaveRole_h__
