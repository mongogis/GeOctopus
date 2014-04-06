#include "Server.h"
#include "port.h"

#include <algorithm>

hpgc::Server * hpgc::Server::m_instance = NULL;

hpgc::IAlgorithmFactory * hpgc::Server::Create(int argc, char ** argv)
{
	Server * server = GetInstance();

	char * name = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (EQUAL(argv[i], "-alg") && i < argc - 1)
		{
			name = argv[++i];
		}
		else
		{
			return NULL;
		}
	}

	auto result =
		std::find_if(std::begin(factories), std::end(factories),
		[name](IAlgorithmFactory * f){ return strcmp(name, f->GetName()); });

	if (result != std::end(factories))
	{
		return *result;
	}
	else
	{
		return NULL;
	}
}

hpgc::Server * hpgc::Server::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new Server();
	}

	return m_instance;
}

void hpgc::Server::DestoryInstance()
{
	if (!m_instance)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

hpgc::Server::~Server()
{

}

void hpgc::Server::AddAlgorithmFactory(IAlgorithmFactory * factory)
{
	this->factories.push_back(factory);
}

void hpgc::Server::RemoveAlgorithmFactory(const char * name)
{
	auto result = std::find_if(std::begin(factories), std::end(factories),
		[name](IAlgorithmFactory * f){ return EQUAL(name, f->GetName()); });

	if (result != std::end(factories))
	{
		factories.remove(*result);
	}
}


