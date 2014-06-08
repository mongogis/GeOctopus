#ifndef common_h__
#define common_h__

#include "rpc.message.pb.h"
#include "VectorBarrel.h"

namespace hpgc {
    void HPGCInit(int argc, const char ** argv);

    struct Record {
        double start_time;
        double end_time;
        int slave;
        int id;

    };

    VectorBarral * BarralFromDataMessage(DataMessage * msg);
    DataMessage  * DataMessageFromBarral(VectorBarral * barral);

    Record  RecordFromTaskMessage(TaskMessage * msg);


}
#endif // common_h__
