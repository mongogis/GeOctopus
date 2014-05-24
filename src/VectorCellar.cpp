#include "VectorCellar.h"
#include <algorithm>

void hpgc::VectorCellar::AddBarrel(VectorBarral * barrel) {
    this->m_barrels.push_back(barrel);
}

hpgc::VectorBarral * hpgc::VectorCellar::GetByIndex(int index)
{
	return m_barrels[index];
}

bool hpgc::VectorCellar::IsEmpty() {
    return this->m_barrels.empty();
}

hpgc::VectorCellar::~VectorCellar() {
}

int hpgc::VectorCellar::size() {
    return this->m_barrels.size();
}
