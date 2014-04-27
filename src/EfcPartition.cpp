#include "EfcPartition.h"
#include "geoalgorithm.format.h"

hpgc::VectorCellar * hpgc::EfcPartition::Partition(VectorMetaData * data)
{
	RegisterVector();
	auto srcds = VectorOpen(data->GetSrcName(), GA_ReadOnly);

	auto cellar = new VectorCellar();
	
	return cellar;
}
