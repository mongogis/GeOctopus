#include "common.h"
#include "rpc.h"

#include <asm/msr.h>
#include <sys/time.h>

namespace hpgc {
    void HPGCInit(int argc, char ** argv) {
        RPCNetwork::Init();
    }

    VectorBarral * BarralFromDataMessage(DataMessage * msg) {
        auto srcds = msg->srcdatasource();
        auto srclayer = msg->srclayer();
        auto dstds = msg->dstdatasource();
        auto dstlayer = msg->dstlayer();
        auto count = msg->features_size();
        std::list<int> feats;
        for (int i = 0; i < count; ++i) {
            feats.push_back(msg->features(i));
        }
        return new VectorBarral(srcds, srclayer, feats, dstds, dstlayer);
    }

    DataMessage * DataMessageFromBarral(VectorBarral * barral) {
        auto dmsg = new DataMessage();
        dmsg->set_srcdatasource(barral->GetSrcDataSource());
        dmsg->set_srclayer(barral->GetSrcLayer());
        dmsg->set_dstdatasource(barral->GetDstDataSource());
        dmsg->set_dstlayer(barral->GetDstLayer());
        std::for_each(barral->GetFeatures().begin(), barral->GetFeatures().end(), 
			[&](int id) { dmsg->add_features(id); } );
        return dmsg;
    }

    Record RecordFromTaskMessage(TaskMessage * msg) {
        Record record;
        record.start_time = msg->starttime();
        record.end_time = msg->endtime();
        record.id = msg->dataindex();
        return record;
    }

	void Sleep(double t) {
		timespec req;
		req.tv_sec = (int)t;
		req.tv_nsec = (int64_t)(1e9 * (t - (int64_t)t));
		nanosleep(&req, NULL);
	}

}

