#include "hpgc.h"

class cvct2gdal_Factory:public hpgc::IGeoAlgFactory
{

public:
	const char * GetName();
	const char * GetDescription();
	hpgc::IGeoAlgorithm * Create(int argc, char ** argv);
	cvct2gdal_Factory();
};

class cvct2gdal:public hpgc::IGeoAlgorithm
{
private:
	hpgc::Barrel *m_barrel;
	char * m_pPara1;
	char * m_pPara2;
public:
	bool Computing();
	hpgc::Barrel * GetBarrel();
	void SetBarrel(hpgc::Barrel*);
	void init(int argc, char ** argv);
	void help();
	cvct2gdal();

};
