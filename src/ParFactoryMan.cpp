#include "FactoryManager.h"
#include "port.h"

#include <algorithm>

hpgc::ParFactoryMan * hpgc::ParFactoryMan::m_instance = NULL;

hpgc::IPartitionFactory * hpgc::ParFactoryMan::FindFactory(const char * pszParName)
{
	ParFactoryMan * m_instance = GetInstance();

	if(pszParName==NULL || pszParName=="")
		pszParName="ECF";

	//void result =
	//	std::find_if(std::begin(factories), std::end(factories),
	//	[name](IPartitionFactory * f){ return strcmp(name, f->GetName()); });

	std::list<IPartitionFactory*>::iterator i=std::begin(factories);
	IPartitionFactory * pParFactory=NULL;

	for (;i!=std::end(factories);i++)
		if (strcmp(pszParName, (*i)->GetName()))
		{
			pParFactory=(*i);
			break;
		}

		return pParFactory;

}

hpgc::ParFactoryMan * hpgc::ParFactoryMan::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new ParFactoryMan();
	}

	return m_instance;
}

void hpgc::ParFactoryMan::DestoryInstance()
{
	if (!m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

hpgc::ParFactoryMan::~ParFactoryMan()
{

}

void hpgc::ParFactoryMan::AddFactory(IPartitionFactory * factory)
{
	this->factories.push_back(factory);
}

void hpgc::ParFactoryMan::RemoveFactory(const char * name)
{
	auto result = std::find_if(std::begin(factories), std::end(factories),
		[name](IPartitionFactory * f){ return EQUAL(name, f->GetName()); });

	if (result != std::end(factories))
	{
		factories.remove(*result);
	}
}


