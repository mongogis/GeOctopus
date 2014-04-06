#ifndef HPGC_INTERFACE_ALGORITHM_H_INCLUDE

#define HPGC_INTEAFACE_LGORITHM_H_INCLUDE 

namespace hpgc { 

class IAlgorithm
{
public:
	virtual bool Run() = 0;
	virtual void PreAlg() = 0;
};

}

#endif