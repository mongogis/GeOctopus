#include "FactoryManager.h"
#include "port.h"

#include <algorithm>

hpgc::AlgFactoryMan * hpgc::AlgFactoryMan::m_instance = NULL;

hpgc::IGeoAlgFactory * hpgc::AlgFactoryMan::FindFactory(const char * pszAlgName)
{
	AlgFactoryMan * AlgFactoryMan = GetInstance();
	if(pszAlgName==NULL || pszAlgName=="")
		return 0;
	//void result =
	//	std::find_if(std::begin(factories), std::end(factories),
	//	[name](IGeoAlgFactory * f){ return strcmp(name, f->GetName()); });
	
	std::list<IGeoAlgFactory*>::iterator i=std::begin(factories);
	//HpgcAlgorithm * pHpgcAlg=NULL;
	IGeoAlgFactory * pAlgorithmFactory=NULL;

	for (;i!=std::end(factories);i++)
		if (strcmp(pszAlgName, (*i)->GetName()))
		{
			pAlgorithmFactory=(*i);
			break;
		}

	return pAlgorithmFactory;

}

hpgc::AlgFactoryMan * hpgc::AlgFactoryMan::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new AlgFactoryMan();
	}

	return m_instance;
}

void hpgc::AlgFactoryMan::DestoryInstance()
{
	if (!m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

hpgc::AlgFactoryMan::~AlgFactoryMan()
{

}

void hpgc::AlgFactoryMan::AddFactory(IGeoAlgFactory * factory)
{
	this->factories.push_back(factory);
}

void hpgc::AlgFactoryMan::RemoveFactory(const char * name)
{
	auto result = std::find_if(std::begin(factories), std::end(factories),
		[name](IGeoAlgFactory * f){ return EQUAL(name, f->GetName()); });

	if (result != std::end(factories))
	{
		factories.remove(*result);
	}
}


