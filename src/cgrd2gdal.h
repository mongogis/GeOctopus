#include "hpgc.h"
using namespace hpgc;

class cgrd2gdal_Factory:public AlgFactory
{
private:
	char * m_FID;
	char * m_Name;
	char * m_Description;
protected:
	bool ParaValidation(int argc, char ** argv);
public:
	long GetID();
	bool SetID();

	char * GetName();
	bool SetName();

	char *	GetDescription();
	bool SetDescription();

	HpgcAlgorithm * Create(int argc, char ** argv);
	cgrd2gdal_Factory();
}

bool cgrd2gdal_Factory::ParaValidation(int argc, char ** argv)
{

}
HpgcAlgorithm* cgrd2gdal_Factory::Create(int argc, char ** argv)
{

}