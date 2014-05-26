#ifndef MessageTag_h__
#define MessageTag_h__

#include "VectorBarrel.h"
#include <mpiobject.h>

// 定义最大缓冲区为2M
#define HPGC_MPI_MAX_BARREL_BUFFER_SIZE 1000000
#define HPGC_MPI_MAX_DATA_SOURCE_NAME_LENGTH 20
#define HPGC_MPI_MAX_LAYER_NAME_LENGTH 20
#define HPGC_MPI_MAX_FEATURE_COUNT 100000

namespace hpgc{
	class MessageTag
	{
	public:
		static const int MSG_TAG_TASK = 1;
		static const int MSG_TAG_TASK_OK = 1;
		static const int MSG_TAG_TASK_WRONG = 0;
		static const int MSG_TAG_DATA = 2;
		static const int MSG_TAG_DATA_OK = 1;
		static const int MSG_TAG_DATA_WRONG = 0;
	};

	struct TaskInfo {
		int IsOk;
		int DataIndex;
		double StartTime;
		double EndTime;

		TaskInfo();
	};

	struct DataInfo{
		int IsOk;
		int DataIndex;
		VectorBarral * Barrel;

		DataInfo();
	};

	MPI_Datatype MPI_Commit_Type_TaskInfo();
	void MPI_Free_Type_TaskInfo();
	void MPI_SendTaskInfo(TaskInfo & info, int process,int tag);
	TaskInfo * MPI_ReceiveTaskInfo(int process,int tag);

	void MPI_Commit_Type_DataInfo();
	void MPI_SendDataInfo(DataInfo & info, int process, int tag);
	DataInfo * MPI_ReceiveDataInfo(int process, int tag);
}

#endif // MessageTag_h__
