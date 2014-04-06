#ifndef HPGCH_VECTOR_CELLAR_H_INCLUDE

#define HPGCH_VECTOR_CELLAR_H_INCLUDE 

#include "ICellar.h"
#include "IBarrel.h"
#include <list>

namespace hpgc{

	class VectorCellar:public ICellar
	{
	public:
		VectorCellar();
		~VectorCellar();



	private:
		std::list<IBarrel *> m_barrels;
	};
}

#endif