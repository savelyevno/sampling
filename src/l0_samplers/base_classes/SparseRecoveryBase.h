//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_SPARSERECOVERYBASE_H
#define L0SAMPLER_SPARSERECOVERYBASE_H

#include "../../../pch/common.pch"

struct SparseRecoveryBase
{
    virtual void update(Int index, Int value)=0;

    virtual Set <pair <Int, Int> > query()=0;
};


#endif //L0SAMPLER_SPARSERECOVERYBASE_H
