#include "hpgc.h"
#include <cpl_string.h>
#include <cpl_conv.h>
#include <cpl_port.h>
#include <cpl_vsi.h>

using namespace hpgc;

ServiceCenter::ServiceCenter()
{
	m_factory_list.push_back(NULL);
}

AlgFactory * ServiceCenter:: create(int argc, char ** argv)
{
	if(m_instance =NULL)
		m_instance=new ServiceCenter();

	char * pszAlg;
	AlgFactory * pfactory=NULL;

	for ( int i = 1; i < argc; i++ )
	{
		if ( EQUAL(argv[i], "-alg") && i < argc - 1 )
		{
			pszAlg = argv[++i];
		}
		else
			return 0;
	}

	for(list<AlgFactory *>::iterator i=m_factory_list.begin();i!=_factory_list.end();i++)
	{
		if (EQUAL((*i)->Fname.c_str(),pszAlg))
		{
			return *i;
		}
	}
	
	return 0;
}

bool ServiceCenter::AddFactory(AlgFactory * pAlgFactory)
{
	m_factory_list.push_back(pAlgFactory);
}

bool ServiceCenter::RemoveFactory(char * pFactoryName)
{
	for(list<AlgFactory *>::iterator i=m_factory_list.begin();i!=m_factory_list.end();i++)
	{
		if (EQUAL((*i)->Fname.c_str(),pFactoryName))
		{
			m_factory_list.remove(*i);
		}
	}
}