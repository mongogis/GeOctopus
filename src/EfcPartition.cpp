#include "EfcPartition.h"
#include "geoalgorithm.format.h"
#include <algorithm>

std::vector<OGRLayer *> GetLayers(OGRDataSource * ds)
{
	std::vector<OGRLayer *> layers;
	auto layerCount = ds->GetLayerCount();
	for (int i = 0; i < layerCount; ++i)
	{
		layers.push_back(ds->GetLayer(i));
	}
	return layers;
}

hpgc::VectorCellar * hpgc::EfcPartition::Partition(VectorMetaData * data)
{
	RegisterVector();
	auto srcds = VectorOpen(data->GetSrcName(), GA_ReadOnly);
	auto srcLayers = GetLayers(srcds);
	std::list<int> srcFeatures;

	auto cellar = new VectorCellar();

	int count = 0;
	int efc_index = 100;
	OGRFeature * current = NULL;

	std::for_each(begin(srcLayers),end(srcLayers), [&](OGRLayer * layer){
		while (true)
		{
			count++;

			if (count <= efc_index)
			{
				current = layer->GetNextFeature();
				if (current != NULL)
				{
					srcFeatures.push_back(current->GetFID());
					continue;
				}
			}

			cellar->AddBarrel(new VectorBarral(srcds->GetName()
				, layer->GetName()
				, srcFeatures));

			srcFeatures.clear();
			count = 0;

			if (current == NULL)
			{
				break;
			}
			else
			{
				current = NULL;
			}
		}
	});

	
	return cellar;
}

