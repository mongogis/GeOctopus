#ifndef HPGC_INTERFACE_DATA_H_INCLUDE

#define HPGC_INTERFACE_DATA_H_INCLUDE 

#include <stack>
namespace hpgc{

	class IData
	{
	public:
	};



	class Barrel
	{
	private:
		char * pszDataSource;
		char * pszLayer;
		char ** flist;
	public:
		char * GetDataSource();
		void SetDataSource();

		char * GetLayer();
		void SetLayer();

		void AddFeature(char *);
		void RemoveFeature(char *);

		char * Packup();
		void unPack(const char *);

		Barrel();
		~Barrel();
	};

	class Cellar
	{
	private:
		std::stack<hpgc::Barrel *> m_barrel_stack;

	public:
		int Count();
		void AddBarrel(hpgc::Barrel *);
		hpgc::Barrel * PopBarrel();
	};

	class MetaData
	{
	public:
		char *GetDataSource();
		char ** GetLayers();
		long GetFeatCount();
	protected:
	private:
		char *m_DataSource;
		char ** m_Layers;

	};
}
#endif