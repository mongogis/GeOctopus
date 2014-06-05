#include "MasterRole.h"
#include <mpiobject.h>
#include <mpimessage.h>
#include <mpioperator.recvmsg.h>
#include "port.debug.h"
#include <geoalgorithm.format.h>
#include "ScopeGuard.h"

int hpgc::MasterRole::Action() {
    ReadyToGo();
    SendFirstBarrel();
    bool IsGameOver = false;
    while (!IsGameOver) {
        TaskInfo * info = ReceiveSlaveMsg();
        ON_SCOPE_EXIT([&info]() {delete info; });
        auto status = GetStatus();
        switch (info->IsOk) {
        case MessageTag::MSG_TAG_TASK_OK : {
            if (m_cellarIndex.empty()) {
                SendNoData(status.MPI_SOURCE);
                m_sleepSlaves.push(status.MPI_SOURCE);
                if (IsAllSlaveOver()) {
                    IsGameOver = true;
                }
            }
            else {
                auto process = m_activeSlaves.front();
                auto dataIndex = m_cellarIndex.front();
                DataInfo data;
                data.IsOk = MessageTag::MSG_TAG_DATA_OK;
                data.DataIndex = dataIndex;
                data.Barrel = m_cellar->GetByIndex(dataIndex);
                SendData(data, process);
                m_cellarIndex.pop();
                m_activeSlaves.pop();
            }
            break;
        }
        case MessageTag::MSG_TAG_TASK_WRONG: {
            m_cellarIndex.push(info->DataIndex);
            break;
        }
        default:
            BUG("ok");
        }
    }
    return 1;
}


hpgc::MasterRole::MasterRole(VectorCellar * cellar) {
    m_cellar = cellar;
    for (auto i = 0; i < m_cellar->size(); ++i) {
        m_cellarIndex.push(i);
    }
}

void hpgc::MasterRole::ReadyToGo() {
    for (auto i = 1; i < m_mpi.GetOurSize(); ++i) {
        auto info = ReceiveSlaveMsg();
        auto status = GetStatus();
        m_activeSlaves.push(status.MPI_SOURCE);
    }
}

void hpgc::MasterRole::SendFirstBarrel() {
    while (!m_activeSlaves.empty()) {
        auto process = m_activeSlaves.front();
        auto dataIndex = m_cellarIndex.front();
        DataInfo data;
        data.IsOk = MessageTag::MSG_TAG_DATA_OK;
        data.DataIndex = dataIndex;
        data.Barrel = m_cellar->GetByIndex(dataIndex);
        SendData(data, process);
        m_cellarIndex.pop();
        m_activeSlaves.pop();
    }
}

hpgc::TaskInfo * hpgc::MasterRole::ReceiveSlaveMsg() {
    return MPI_ReceiveTaskInfo(MPI_ANY_SOURCE, MessageTag::MSG_TAG_TASK);
}

void hpgc::MasterRole::SendNoData(int process) {
    DataInfo info;
    info.IsOk = MessageTag::MSG_TAG_DATA_WRONG;
    info.DataIndex = -1;
    info.Barrel = NULL;
    SendData(info, process);
}

void hpgc::MasterRole::SendData(DataInfo & data, int process) {
    MPI_SendDataInfo(data, process, MessageTag::MSG_TAG_DATA);
}

bool hpgc::MasterRole::IsAllSlaveOver() {
    return m_sleepSlaves.size() == (m_mpi.GetOurSize() - 1);
}
