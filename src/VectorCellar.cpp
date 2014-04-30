#include "VectorCellar.h"
#include <algorithm>

void hpgc::VectorCellar::AddBarrel(VectorBarral * barrel) {
    this->m_barrels.push_back(barrel);
}

hpgc::VectorBarral * hpgc::VectorCellar::PopBarrel() {
    auto it = m_barrels.back();
    m_barrels.pop_back();
    return it;
}

bool hpgc::VectorCellar::IsEmpty() {
    return this->m_barrels.empty();
}

hpgc::VectorCellar::~VectorCellar() {
}

int hpgc::VectorCellar::size() {
    return this->m_barrels.size();
}
