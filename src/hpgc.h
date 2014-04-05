#include <list>
#include <stdlib.h>
using namespace std;
namespace hpgc{

	class Role
	{

	};

	class Process
	{
		Role role;
	public:
		bool isRole(Role role);
	};

	class MetaData
	{
	public:
	};

	class Cellar
	{
	};

	class Barrel
	{
	};

	class geo_algorithm{
	public:
		bool Computing();
	};

	class hpgc_scheduler
	{
		std::list<Role> roles;
		std::list<Process> processes;
		std::list<Cellar> cellars;
	public:
		void Start();
	};

	class hpgc_partition
	{
	public:
		Cellar * Partitioning();
	};



	class hpgc_algorithm{
		hpgc_scheduler scheduler;
		hpgc_partition partition;
		geo_algorithm algorithm;
	public:
		bool Run();
	}; 

	class hpgc_factory
	{
	private:
		long fctid;
		string fctname;
		string description;
	public:
		long FID;
		string Fname;
		string	description;

		hpgc_algorithm * create();
		hpgc_factory(int argc, char ** argv);
	};


	class service_center
	{
	private:
		static list<hpgc_factory *> _factory_list;
	public:
		service_center();
		static hpgc_factory * create(int argc, char ** argv);
	};

}