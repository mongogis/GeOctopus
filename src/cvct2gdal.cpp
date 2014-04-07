#include "cvct2gdal.h"
#include "port.h"

bool cvct2gdal::Computing()
{
	// print my barrel;
	printf(m_barrel->Packup());
	return 1;
};
hpgc::Barrel * cvct2gdal::GetBarrel()
{
	return m_barrel;
};
void cvct2gdal::SetBarrel(hpgc::Barrel* pBarrel)
{
	m_barrel=pBarrel;
};

cvct2gdal::cvct2gdal()
{
	m_barrel=new hpgc::Barrel();
};

void cvct2gdal::init(int argc, char ** argv)
{
	for ( int i = 1; i < argc; i++ )
	{
		if ( EQUAL(argv[i], "-p1") )
		{
			//papszLayers = CSLAddString(papszLayers, argv[++i]);
			m_pPara2=argv[++i];
		}

		else if ( EQUAL(argv[i], "-p2") && i < argc - 1 )
		{
			m_pPara1 = argv[++i];
		}
		else
		{
			help();
		}
	}
};

void cvct2gdal::help()
{
	printf(	"cvct2gdal -p1 para1 -p2 para2\n");
}