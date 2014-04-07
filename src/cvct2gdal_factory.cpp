#include "hpgc.h"
#include "cvct2gdal.h"
#include "HpgcAlgorithm.h"

const char * cvct2gdal_Factory::GetName()
{
	return "cvct2gdal";
}
const char * cvct2gdal_Factory::GetDescription()
{
	return "将中国地理数据矢量交换格式VCT转到GDAL支持的数据格式";
}


hpgc::IGeoAlgorithm * cvct2gdal_Factory::Create(int argc, char ** argv)
{
	hpgc::IGeoAlgorithm *pIGeoAlgorithm=new cvct2gdal();
	pIGeoAlgorithm->init(argc,argv);
	return pIGeoAlgorithm;
}
cvct2gdal_Factory::cvct2gdal_Factory()
{
}