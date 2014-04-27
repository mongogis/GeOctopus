#ifndef HPGC_ROLE_H_INCLUDE

#define HPGC_ROLE_H_INCLUDE

#include "VectorBarrel.h"

namespace hpgc{

	class IRole
	{
	public:
		virtual int Action(VectorBarral * barral) = 0;
	};

}

#endif