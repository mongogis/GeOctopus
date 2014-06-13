#include "MasterRole.h"
#include "port.debug.h"
#include "ScopeGuard.h"
#include "rpc.message.pb.h"
#include "common.h"

#include <glog/logging.h>
#include <geoalgorithm.format.h>

namespace hpgc {

    struct Taskid {
        int id;
        Taskid(int i) :
            id(i) {
        }

		bool operator<(const Taskid& b) const {
			return id < b.id;
		}
    };



    struct TaskState {
        enum Status {
            PENDING = 0, ACTIVE = 1, FINISHED = 2
        };

        TaskState(Taskid id, VectorBarral * data) :
            id(id), status(PENDING), data(data), slave(-1) {
        }

        Taskid id;
        Status status;
        int slave;
        VectorBarral * data;
    };

    static std::map<Taskid, TaskState *> m_task ;

    TaskState * GetPendingTask() {
        auto result = std::find_if(m_task.begin(), m_task.end(),
        [](std::pair<const Taskid, TaskState *> & pair) {
            if (pair.second->status == TaskState::PENDING) {
                return true;
            }
            return false;
        }
                                  );
        if (result != m_task.end()) {
            return (*result).second;
        }
        else {
            return nullptr;
        }
    }

    bool CheckAllFinished() {
        auto result = std::find_if(m_task.begin(), m_task.end(),
        [](std::pair<const Taskid, TaskState *> & pair) {
            if (pair.second->status == TaskState::PENDING ||
                    pair.second->status == TaskState::ACTIVE) {
                return true;
            }
            return false;
        }
                                  );
        if (result != m_task.end()) {
            return false;
        }
        else {
            return true;
        }
    }

    int MasterRole::Action() {
        TaskState * task = nullptr;
        DataMessage * drequest = nullptr;
        while (m_masterRuning) {
            if (CheckAllFinished()) {
                m_masterRuning = false;
                break;
            }
            /// dispatch task
            task = GetPendingTask();
            if (task != nullptr && !m_activeSlaves.empty()) {
                int slave = m_activeSlaves.front();
                m_activeSlaves.pop();
                drequest = DataMessageFromBarral(task->data);
                ON_SCOPE_EXIT([&]() {delete drequest; });
                m_net->Send(slave, WORKER_RUN_TASK, *drequest);
                task->slave = slave;
                task->status = TaskState::ACTIVE;
            }
            // check active task
            std::for_each(m_task.begin(), m_task.end(),
            [&](std::pair<const Taskid, TaskState *> & pair) {
                if (pair.second->status == TaskState::ACTIVE) {
                    int source = -1;
                    TaskMessage tRequest;
                    if (m_net->TryRead(pair.second->slave, WORKER_TASK_DONE, &tRequest, &source)) {
                        Record stat = RecordFromTaskMessage(&tRequest);
                        stat.slave = pair.second->slave;
                        m_statistics.push_back(stat);
                        pair.second->status = TaskState::FINISHED;
                        m_activeSlaves.push(pair.second->slave);
                    }
                }
            } // function
            );// for_each
        }
        return 0;
    }

    MasterRole::MasterRole(VectorCellar * cellar) {
        m_masterRuning = true;
        m_net = RPCNetwork::Get();
        for (int i = 0; i < cellar->size(); ++i) {
            m_task[Taskid(i)] = new TaskState(Taskid(i), cellar->GetByIndex(i));
        }

        for (int i = 0; i < m_net->Size()-1; ++i) {
            RegisterWorkerRequest req;
            int src = 0;
            m_net->Read(hpgc::ANY_SOURCE, REGISTER_WORKER, &req , &src);
            m_activeSlaves.push(src);
			LOG(INFO) <<" from "<<src<<" to "<<m_net->Id();
        }
    }

    MasterRole::~MasterRole() {
		for (int i = 0; i < m_net->Size()-1;++i)
		{
			EmptyMessage req;
			m_net->Send(i + 1, WORKER_FINALIZE,req);
		}
    }




}