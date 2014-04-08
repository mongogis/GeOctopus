#ifndef HPGCH_VECTOR_CELLAR_H_INCLUDE

#define HPGCH_VECTOR_CELLAR_H_INCLUDE 

#include "VectorBarrel.h"

#include <list>

namespace hpgc{

	class VectorCellar
	{
	public:
		virtual void AddBarrel(VectorBarral * barrel) ;

		virtual VectorBarral * PopBarrel() ;

		virtual bool IsEmpty() ;

		~VectorCellar();

	private:
		std::list<VectorBarral * > m_barrels;
	};
}

#endif