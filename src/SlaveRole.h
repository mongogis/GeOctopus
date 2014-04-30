#ifndef SlaveRole_h__
#define SlaveRole_h__

#include "IRole.h"
#include "IV2VAlgorithm.h"

namespace hpgc{
	class SlaveRole : public IRole
	{
	public:
		virtual int Action();
		SlaveRole(IV2VAlgorithm * task);
	private:
		IV2VAlgorithm * m_alg;
	};
}
#endif // SlaveRole_h__
