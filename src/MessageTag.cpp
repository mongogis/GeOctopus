#include "MessageTag.h"
#include "port.debug.h"

#include <port.designpattern.h>
#include <mpioperator.recvmsg.h>
#include <mpioperator.sendmsg.h>

void hpgc::MPI_SendTaskInfo(TaskInfo & info, int process, int tag)
{
}

void hpgc::MPI_SendDataInfo(DataInfo & info, int process, int tag)
{
}

hpgc::TaskInfo * hpgc::MPI_ReceiveTaskInfo(int process, int tag)
{
	return new hpgc::TaskInfo();
}

hpgc::DataInfo * hpgc::MPI_ReceiveDataInfo(int process, int tag)
{
	return new hpgc::DataInfo();
}

struct MPI_Type_TaskInfo{
	hpgc::TaskInfo m_Temp;
	MPI_Datatype m_NewMPIProInfo;
	MPI_Datatype m_OldMPIProInfo[3];
	int m_BlockLens[3];
	MPI_Aint m_Displs[3];

	MPI_Type_TaskInfo();
};

MPI_Type_TaskInfo::MPI_Type_TaskInfo()
{
	MPI_Get_address(&m_Temp.IsOk, m_Displs);
	MPI_Get_address(&m_Temp.StartTime, m_Displs + 1);
	m_Displs[2] = sizeof(hpgc::TaskInfo);
	m_Displs[1] = m_Displs[1] - m_Displs[0];
	m_Displs[0] = 0;
	m_BlockLens[0] = 2;
	m_BlockLens[1] = 2;
	m_BlockLens[2] = 1;
	m_OldMPIProInfo[0] = MPI_INT;
	m_OldMPIProInfo[1] = MPI_DOUBLE;
	m_OldMPIProInfo[2] = MPI_UB; //数据的上界
	MPI_Type_struct(3, m_BlockLens, m_Displs, m_OldMPIProInfo, &m_NewMPIProInfo);
	MPI_Type_commit(&m_NewMPIProInfo);
}

MPI_Datatype hpgc::MPI_Commit_Type_TaskInfo()
{
	MPI_Type_TaskInfo * info = port::Singleton<MPI_Type_TaskInfo>::CreateInstance();
	return info->m_NewMPIProInfo;
}

void hpgc::MPI_Free_Type_TaskInfo()
{
	MPI_Type_TaskInfo * info = port::Singleton<MPI_Type_TaskInfo>::CreateInstance();
	MPI_Type_free(&info->m_NewMPIProInfo);
	port::Singleton<MPI_Type_TaskInfo>::DestoryInstance();
}

struct MPI_Type_DataInfo
{
	int DataSourceNameLength;
	int LayerNameLength;
	int FeatureCount;

	MPI_Type_DataInfo();
};

MPI_Type_DataInfo::MPI_Type_DataInfo()
{
	DataSourceNameLength = HPGC_MPI_MAX_DATA_SOURCE_NAME_LENGTH;
	LayerNameLength = HPGC_MPI_MAX_LAYER_NAME_LENGTH;
	FeatureCount = HPGC_MPI_MAX_FEATURE_COUNT;
}

hpgc::TaskInfo::TaskInfo()
{

}

hpgc::DataInfo::DataInfo()
{

}
