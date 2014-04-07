#include "FactoryManager.h"
#include "port.h"

#include <algorithm>

hpgc::SchFactoryMan * hpgc::SchFactoryMan::m_instance = NULL;

hpgc::ISchedulerFactory * hpgc::SchFactoryMan::FindFactory(const char *pszSchName)
{
	SchFactoryMan * m_instance = GetInstance();

	if(pszSchName==NULL || pszSchName=="")
		pszSchName="MasterSlave";
	
	//void result =
	//	std::find_if(std::begin(factories), std::end(factories),
	//	[name](IGeoAlgFactory * f){ return strcmp(name, f->GetName()); });

	std::list<ISchedulerFactory*>::iterator i=std::begin(factories);
	//HpgcAlgorithm * pHpgcAlg=NULL;
	ISchedulerFactory * pSchFactory=NULL;

	for (;i!=std::end(factories);i++)
		if (strcmp(pszSchName, (*i)->GetName()))
		{
			pSchFactory=(*i);
			break;
		}

		return pSchFactory;

}

hpgc::SchFactoryMan * hpgc::SchFactoryMan::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new SchFactoryMan();
	}

	return m_instance;
}

void hpgc::SchFactoryMan::DestoryInstance()
{
	if (!m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

hpgc::SchFactoryMan::~SchFactoryMan()
{

}

void hpgc::SchFactoryMan::AddFactory(ISchedulerFactory * factory)
{
	this->factories.push_back(factory);
}

void hpgc::SchFactoryMan::RemoveFactory(const char * name)
{
	auto result = std::find_if(std::begin(factories), std::end(factories),
		[name](ISchedulerFactory * f){ return EQUAL(name, f->GetName()); });

	if (result != std::end(factories))
	{
		factories.remove(*result);
	}
}


