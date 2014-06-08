#include "SlaveRole.h"
#include "port.debug.h"
#include "timer.h"
#include "common.h"
#include "ScopeGuard.h"

#define FLAGS_sleep_time 3

namespace hpgc {


    int SlaveRole::Action() {
        RegisterWorkerRequest req;
        req.set_id(Id());
        m_net->Send(0, REGISTER_WORKER, req);
        DataMessage dRequest;
        while (m_workRunning) {
            Timer idle;
            while (!m_net->TryRead(0, WORKER_RUN_TASK, &dRequest)) {
                Sleep(FLAGS_sleep_time);
            }
            if (!m_workRunning) {
                return;
            }
            m_taskRunning = true;
            TaskMessage kRequest;
            VectorBarral * barrel = BarralFromDataMessage(&dRequest);
            ON_SCOPE_EXIT([&]() {delete barrel; });
            kRequest.set_starttime(Now());
            if (m_alg->Compute(barrel)) {
                kRequest.set_type(TASK_OK);
            }
            else {
                kRequest.set_type(TASK_WRONG);
            }
            kRequest.set_endtime(Now());
            m_taskRunning = false;
            m_net->Send(0, WORKER_TASK_DONE, kRequest);
        }
        return 0;
    }

    SlaveRole::SlaveRole(IV2VAlgorithm * task, MetaData * dst) {
        m_dst = dst;
        m_alg = task;
        m_net = RPCNetwork::Get();
        m_workRunning = true;
        m_taskRunning = false;
        RegisterCallback(WORKER_FINALIZE, new EmptyMessage(),
                         new EmptyMessage, &SlaveRole::HandleGameOver, this);
    }

    int SlaveRole::Id() {
        return m_net->id();
    }

    void SlaveRole::HandleGameOver(const EmptyMessage & req, EmptyMessage * resp,
                                   const RPCInfo & rpc) {
        while (m_taskRunning) {
            Sleep(FLAGS_sleep_time);
        }
        m_taskRunning = false;
        m_workRunning = false;
    }

    SlaveRole::~SlaveRole() {
        m_workRunning = false;
    }





}
