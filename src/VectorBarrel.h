#ifndef HPGCH_VECTOR_BARREL_H_INCLUDE

#define HPGCH_VECTOR_BARREL_H_INCLUDE

#include <list>

namespace hpgc{

	class VectorBarral
	{

	public:

		std::string GetDataSource();

		std::string GetLayer();

		std::list<int> GetFeatures();

		void SetDataSource(std::string datasource);

		void SetLayer(std::string layer);

		void SetFeatures(std::list<int> feats);

		VectorBarral(std::string datasource, std::string layer, std::list<int> features)
			:m_datasource(datasource)
			,m_layer(layer)
			,m_features(features){

		};

		VectorBarral(){};

	private:
		std::string m_datasource;
		std::string m_layer;
		std::list<int> m_features;
	};

}

#endif