#ifndef HPGC_FRAMEWORK_H_INCLUDE

#define HPGC_FRAMEWORK_H_INCLUDE

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

/// @brief 定义hpgc framework 骨架。
///
/// 命名空间hpgc下只framework骨架类的东西，为所有地理算法所公用的部分。
/// 如MPIObject, framework的公共接口，具体地理算法所实现的类不包含在其中。

#include "IAlgorithm.h"
#include "IBarrel.h"
#include "ICellar.h"
#include "IData.h"
#include "IFactory.h"
	
#endif