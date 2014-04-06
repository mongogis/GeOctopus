#ifndef HPGC_ALGORITHM_H_INCLUDE

#define HPGC_ALGORITHM_H_INCLUDE 

namespace hpgc { 

class IAlgorithm
{
public:
	virtual bool Run() = 0;
};

}

#endif