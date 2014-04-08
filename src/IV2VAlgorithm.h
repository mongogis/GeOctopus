#ifndef V2VAlgorithm_h__
#define V2VAlgorithm_h__

#include "VectorBarrel.h"

namespace hpgc{
	class IV2VAlgorithm{
	public:
		virtual bool Compute(VectorBarral * src , VectorBarral * dst) = 0;
	};
}

#endif // V2VAlgorithm_h__
