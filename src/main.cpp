#include "hpgc.h"

int main(int argc, char ** argv){
	hpgc::Factory * factory = new hpgc::Factory(argc, argv);
	hpgc::Algorithm alg = factory->Create();
	alg.Run();
	return 1;
}