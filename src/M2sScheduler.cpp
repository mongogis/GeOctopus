#include "M2sScheduler.h"
#include "MasterRole.h"
#include "SlaveRole.h"
#include "vector.metadata.h"
#include "ScopeGuard.h"
#include "rpc.h"
#include "port.debug.h"

#include <geoalgorithm.format.h>

void hpgc::M2sScheduler::Work(IV2VAlgorithm * task,
                              HpgcVectorAlgorithm * hpgcAlg) {

	int id = RPCNetwork::Get()->Id();
	int size = RPCNetwork::Get()->Size();
	BUG(id);
    if (id == 0) {
        auto meta = hpgcAlg->GetMetaData();
        auto partition = hpgcAlg->GetPartition();
        VectorCellar * srcCellar = partition->Partition(meta);

		MasterRole node = { srcCellar };
		BUG("Master");
		//node.Action();
    }
    else {
		SlaveRole node = { task };
		BUG("Slave");
		//node.Action();
    }
}



