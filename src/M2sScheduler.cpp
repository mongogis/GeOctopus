#include "M2sScheduler.h"
#include "MasterRole.h"
#include "SlaveRole.h"
#include "vector.metadata.h"
#include "ScopeGuard.h"
#include "rpc.h"

#include <geoalgorithm.format.h>

void hpgc::M2sScheduler::Work(IV2VAlgorithm * task,
                              HpgcVectorAlgorithm * hpgcAlg) {

	int id = RPCNetwork::Get()->id();
    IRole * node = NULL;
    if (id == 0) {
        auto meta = hpgcAlg->GetMetaData();
        auto partition = hpgcAlg->GetPartition();
        // TODO generate layer
        auto dstds = VectorOpen(meta->GetDstMetaData()->GetDataSourceName(), GA_Update);
        ON_SCOPE_EXIT([&dstds]() {OGRDataSource::DestroyDataSource(dstds); });
        auto dstlayer = dstds->CreateLayer(meta->GetDstMetaData()->GetLayerName(),
                                           NULL);
        VectorCellar * srcCellar = partition->Partition(meta);
        node = new MasterRole(srcCellar);
    }
    else {
        auto dst = hpgcAlg->GetMetaData()->GetDstMetaData();
        node = new SlaveRole(task, dst);
    }
    node->Action();
}



