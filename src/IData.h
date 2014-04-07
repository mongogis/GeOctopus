#ifndef HPGC_INTERFACE_DATA_H_INCLUDE

#define HPGC_INTERFACE_DATA_H_INCLUDE 


namespace hpgc{

	class IData
	{
	public:
	};

	class Cellar
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

}
#endif