#ifndef VectorPartition_h__
#define VectorPartition_h__

#include "VectorCellar.h"
#include "vector.metadata.h"

namespace hpgc{
	class IVectorPartition
	{
	public:
		virtual VectorCellar * Partition(MetaData * meta) = 0;

	};
}
#endif // VectorPartition_h__
