#include "Server.h"
#include "IAlgorithmFactory.h"
#include <cpl_string.h>
#include <cpl_conv.h>
#include <cpl_port.h>
#include <cpl_vsi.h>

hpgc::IAlgorithmFactory * hpgc::Server::Create(int argc, char ** argv)
{
	if(m_instance =NULL)
		m_instance=new ServiceCenter();

	char * pszAlg;
	IAlgorithmFactory * pfactory=NULL;

	for ( int i = 1; i < argc; i++ )
	{
		if ( EQUAL(argv[i], "-alg") && i < argc - 1 )
		{
			pszAlg = argv[++i];
		}
		else
			return 0;
	}

	for(std::list<IAlgorithmFactory *>::iterator i=m_instance->m_factory_list.begin();i!=m_instance->m_factory_list.end();i++)
	{
		if (EQUAL((*i)->GetName.c_str(),pszAlg))
		{
			return *i;
		}
	}
	
	return 0;
}

hpgc::Server::ServiceCenter()
{
	m_factory_list.push_back(NULL);
}

bool hpgc::Server::AddFactory(IAlgorithmFactory * pAlgFactory)
{
	m_factory_list.push_back(pAlgFactory);
}

bool hpgc::Server::RemoveFactory(char * pFactoryName)
{
	for(std::list<IAlgorithmFactory *>::iterator i=m_factory_list.begin();i!=m_factory_list.end();i++)
	{
		if (EQUAL((*i)->GetName.c_str(),pFactoryName))
		{
			m_factory_list.remove(*i);
		}
	}
}
