#include "hpgc.h"

int hpgc::Cellar::Count()
{
	return m_barrel_stack.size();
};
void hpgc::Cellar::AddBarrel(hpgc::Barrel *pBarrel)
{
	m_barrel_stack.push(pBarrel);
};
hpgc::Barrel * hpgc::Cellar::PopBarrel()
{
	hpgc::Barrel * pBarrel=m_barrel_stack.top();
	m_barrel_stack.pop();
	return pBarrel;
};