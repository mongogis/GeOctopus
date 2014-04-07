#ifndef HPGC_IFactory_H_INCLUDE

#define HPGC_IFactory_H_INCLUDE 

#include "port.designpattern.h"
#include "IFactory.h" 

#include <list>

namespace hpgc{

	class FactoryManager
	{
	public:
		void * FindFactory(const char *);
		void AddFactory(void * );
		void RemoveFactory(const char * );
	};

	class AlgFactoryMan:public FactoryManager
	{
	public:
		IGeoAlgFactory * FindFactory(const char	*);

		void AddFactory(IGeoAlgFactory * );

		void RemoveFactory(const char * );

		static AlgFactoryMan * GetInstance();

		static void DestoryInstance();

	private:
		static AlgFactoryMan * m_instance;

		std::list<IGeoAlgFactory *> factories;

		AlgFactoryMan(){};

		AlgFactoryMan(const AlgFactoryMan &);

		~AlgFactoryMan();
	};

	class SchFactoryMan:public FactoryManager
	{
	public:
		ISchedulerFactory * FindFactory(const char	*);

		void AddFactory(ISchedulerFactory * );

		void RemoveFactory(const char * );

		static SchFactoryMan * GetInstance();

		static void DestoryInstance();

	private:
		static SchFactoryMan * m_instance;

		std::list<ISchedulerFactory *> factories;

		SchFactoryMan(){};

		SchFactoryMan(const SchFactoryMan &);

		~SchFactoryMan();
	};

	class ParFactoryMan:public FactoryManager
	{
	public:
		IPartitionFactory * FindFactory(const char	*);

		void AddFactory(IPartitionFactory * );

		void RemoveFactory(const char * );

		static ParFactoryMan * GetInstance();

		static void DestoryInstance();

	private:
		static ParFactoryMan * m_instance;

		std::list<IPartitionFactory *> factories;

		ParFactoryMan(){};

		ParFactoryMan(const ParFactoryMan &);

		~ParFactoryMan();
	};
}

#endif