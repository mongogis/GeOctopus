/**
* @file hpgc.h
* @brief 定义hpgc framework各部分接口
*
* hpgc framework 的目的是为了简化高性能地理算法的开发难度，使串行算法通过实现一些接口并行化。
* 为了重用和解耦各个部件，hpgc framework 设计了Partiton, Scheduler, HpgcAlgotithm, AlgFactory等组件。
* Partition负责数据划分，Scheduler负责进程调度，HpgcAlgorithm封装一个并行算法，AlgFactory用于创建一个并行算法。
* hpgc framework 构建在MPI和GDAL类库之上，希望达到以下目的：
* （1）新算法通过实现这些接口可以很容易的接入并行框架中去；
* （2）并行处理进程调度模式灵活易扩展；
* （3）数据划分策略灵活易扩展；
* （4）面向高性能地理计算封装MPI，简化MPI的调用过程。
*
* @author mongogis@gmail.com
* @version 0.1
* @date 2014
*/


#include <list>
#include <stdlib.h>

/// @brief 定义hpgc framework 骨架。
///
/// 命名空间hpgc下只framework骨架类的东西，为所有地理算法所公用的部分。
/// 如MPIObject, framework的公共接口，具体地理算法所实现的类不包含在其中。
namespace hpgc
{
	
class Role
{

};

class Process
{
	Role role;
	public:
	bool isRole(Role role);
};

class MetaData
{
	public:
};

class Cellar
{

};

class Barrel
{
public:


};

class GeoAlgorithm{
public:
	bool Computing();
};

class Scheduler
{
	std::list<Role> roles;
	std::list<Process> processes;
	std::list<Cellar> cellars;
public:
	void Start();
};

class SchFactory
{
public:
	Scheduler * Create(int argc, char ** argv);
};

/// @brief 数据划分实际执行者
/// 
/// Partition将地理数据划分成子块，每个子块使用Barrel描述，并将结果置于容器Cellar中。
/// Partition通过分析元数据划分数据，具体划分过程尤其子类完成。
class Partition
{
public:
	Cellar * Partitioning();
};

class ParFactory
{
public:
	Partition * Create(int argc, char ** argv);
};
/// @brief 并行地理算法，由Scheduler，Partition，GeoAlgorithm构成
///
/// HpgcAlgorithm是并行算法各个部件的组合类，是并行算法的实际执行者，代表着并行地理算法。
/// HpgcAlgorithm最重要的方法是@ref Run, 其按照一定的顺序组织算法各部分的调用。
class HpgcAlgorithm
{
private:
	Scheduler m_scheduler;
	Partition m_partition;
	GeoAlgorithm m_geoalgorithm;
protected:
	virtual bool init();
	virtual bool PreAlg();
public:
	std::list<Barrel> Cellar;
	bool Run()
	{
		/// @todo 动态创建进程

		// 算法参数解析 init();
		// 数据准备 PreAlg();
		// 数据划分 Cellar=m_partition.partitioning();
		// 进程调度 m_scheduler.start();
	};
};

/// @brief 根据命令行参数实例化并行地理算法
/// 
/// AlgFactory首先对参数进行预判断@ref ParaValidation, 遇到问题退出；
/// 但AlgFactory最重要的功能是实例化对应的并行地理算法(@ref HpgcAlgorithm)，完成一个并行算法
/// 数据划分策略(@ref ParFactory)和进程调度策略(@ref SchFactory)的解析与选择。
/// 
/// 每个并行算法必须实现其对应的factory，继承自AlgFactory，并重写相应的算法创建方法；
/// 每个并行算法的factory必须指定一个独立唯一的标识码(ID)以及名称(Name),
/// hpgc framework依据算法的标识码或者名称识别和调用相应算法。
class AlgFactory
{
protected:
	virtual bool ParaValidation(int argc, char ** argv); ///< 解析验证传入参数
public:
	long GetID();
	bool SetID();

	char * GetName();
	bool SetName();

	char *	GetDescription();
	bool SetDescription();

	HpgcAlgorithm * Create(int argc, char ** argv)
	{
		// 参数验证 ParaValidation
		// 进程调度策略解析，scheduler = SchFactory.Create(argc,argv);
		// 数据划分策略解析，partition = ParFactory.Create(argc,argv);
		// 实例化并行地理算法，HpgcAlgorithm hpgcAlgorithm = new HpgcScanline(); HpgcScanline是HpgcAlgorithm子类
	};
	AlgFactory();
};

/// @brief 依据命令行参数找出对应并行算法的创建工厂
///
/// ServiceCenter中维护一张整个hpgc framework中支持的并行算法索引表，表中记录了每个算法的标识码和名称。
/// ServiceCenter依据传入参数，通过查找算法索引表，实例化相应并行算法的创建工厂。
/// hpgc framework通过ServiceCenter以类似插件的形式动态的维护其支持的并行地理算法。
class ServiceCenter
	{
	private:
		std::list<AlgFactory *> m_factory_list;
		static ServiceCenter * m_instance;
		ServiceCenter();
	public:
		bool AddFactory(AlgFactory *);
		bool RemoveFactory(char * );
		static AlgFactory * Create(int argc, char ** argv)
		{
			// 查找m_factory_list，找出相应的AlgFactory
		};
	};

}