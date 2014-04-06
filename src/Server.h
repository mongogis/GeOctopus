#ifndef HPGC_SERVER_H_INCLUDE

#define HPGC_SERVER_H_INCLUDE 

#include "port.designpattern.h"
#include "IAlgorithmFactory.h" 

#include <list>

namespace hpgc{

	class Server 
	{
	public:
		IAlgorithmFactory * Create(int argc, char ** argv);

		void AddAlgorithmFactory(IAlgorithmFactory * factory);

		void RemoveAlgorithmFactory(const char * name);

		static Server * GetInstance();

		static void DestoryInstance();

	private:
		static Server * m_instance;

		std::list<IAlgorithmFactory *> factories;

		Server(){};

		Server(const Server &){};

		~Server();
	};
}

#endif