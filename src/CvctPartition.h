#ifndef CvctPartition_h__
#define CvctPartition_h__

#include "IVectorPartition.h"

namespace hpgc{
	class CvctPartition:public IVectorPartition
	{
	public:
		virtual VectorCellar * Partition();
	};
}
#endif // CvctPartition_h__
