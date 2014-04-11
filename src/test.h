#ifndef cvct2gdal_h__
#define cvct2gdal_h__

#include "IV2VAlgorithm.h"

namespace hpgc{

	class Test: public IV2VAlgorithm
	{
	public:
		virtual bool Compute(VectorBarral * src, VectorBarral * dst);
	};
}

#endif // cvct2gdal_h__

