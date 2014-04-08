#ifndef VectorPartition_h__
#define VectorPartition_h__

#include "VectorCellar.h"

namespace hpgc{
	class IVectorPartition
	{
	public:
		virtual VectorCellar * Partition() = 0;

	};
}
#endif // VectorPartition_h__
