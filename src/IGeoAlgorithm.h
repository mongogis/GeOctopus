#ifndef HPGC_GEOALGORITHM_H_INCLUDE

#define HPGC_GEOALGORITHM_H_INCLUDE 

namespace hpgc{

	class IGeoAlgorithm
	{
	public:
		virtual void Init() = 0;
		virtual bool Computing() = 0;
	};

}

#endif