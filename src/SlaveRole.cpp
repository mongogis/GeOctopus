#include "SlaveRole.h"
#include <mpiobject.h>
#include <mpimessage.h>
#include <mpioperator.sendmsg.h>
#include "port.debug.h"
#include "MessageTag.h"

int hpgc::SlaveRole::Action() {
    ReadyToGo();
    bool isGameOver = false;
    while (!isGameOver) {
        auto data = ReceiveMasterMsg();
        switch (data->IsOk) {
        case MessageTag::MSG_TAG_DATA_OK: {
            double startTime = m_mpi.GetNow();
            auto status = m_alg->Compute(data->Barrel);
            double endTime = m_mpi.GetNow();
            TaskInfo info;
            info.DataIndex = data->DataIndex;
            info.StartTime = startTime;
            info.EndTime = endTime;
            info.IsOk = status;
            SendTaskInfo(info);
            break;
        }
        case MessageTag::MSG_TAG_DATA_WRONG: {
            isGameOver = true;
            break;
        }
        default: {
            BUG("something is wrong");
        }
        }
    }
    return 1;
}

hpgc::SlaveRole::SlaveRole(IV2VAlgorithm * task, MetaData * dst) {
    m_alg = task;
    m_dst = dst;
}

void hpgc::SlaveRole::ReadyToGo() {
    for (auto i = 1; i < m_mpi.GetOurSize(); ++i) {
        TaskInfo info;
        info.IsOk = MessageTag::MSG_TAG_TASK_OK;
        SendTaskInfo(info);
    }
}

hpgc::DataInfo * hpgc::SlaveRole::ReceiveMasterMsg() {
    return MPI_ReceiveDataInfo(m_mpi.GetMaster(), MessageTag::MSG_TAG_DATA);
}

void hpgc::SlaveRole::SendTaskInfo(TaskInfo info) {
    MPI_SendTaskInfo(info, m_mpi.GetMaster(), MessageTag::MSG_TAG_TASK);
}
