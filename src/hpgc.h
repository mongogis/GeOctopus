#include <list>

namespace hpgc{

class Factory{
public:
	Algorithm & Create();
	Factory(int argc, char ** argv);
};

class Algorithm{
	Scheduler scheduler;
	Partition partition;
	Combinator combinator;
public:
	bool Run();
}; 

class Combinator{
public:
	bool Computing();
};

class Cellar
{
};

class Barrel
{
};

class Scheduler
{
	std::list<Role> roles;
	std::list<Process> processes;
	std::list<Cellar> cellars;
public:
	void Start();
};

class Role{

};

class Process{
	Role role;
public:
	bool isRole(Role role);
};

class Partition
{
public:
	Cellar * Partitioning();
};

class MetaData
{
public:
};


}