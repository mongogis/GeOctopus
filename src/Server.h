#ifndef HPGC_SERVER_H_INCLUDE

#define HPGC_SERVER_H_INCLUDE 

#include "port.designpattern.h"
#include "IAlgorithmFactory.h" 

namespace hpgc{

	class Server 
	{
	private:
		ServiceCenter();
		Server m_instance;
		std::list<IAlgorithmFactory *> m_factory_list;
	public:
		static IAlgorithmFactory * Create(int argc, char ** argv);
		bool AddFactory(IAlgorithmFactory * pAlgFactory);
		bool RemoveFactory(char * pFactoryName);
	};
}

#endif
