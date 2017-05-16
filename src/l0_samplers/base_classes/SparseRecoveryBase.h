//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_SPARSERECOVERYBASE_H
#define L0SAMPLER_SPARSERECOVERYBASE_H

#include "../../../pch/common.pch"

struct SparseRecoveryBase
{
    void update(Int index, Int value);

    set <pair <Int, Int> > query();
};


#endif //L0SAMPLER_SPARSERECOVERYBASE_H
