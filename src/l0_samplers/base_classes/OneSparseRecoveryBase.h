//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_ONESPARSERECOVERYBASE_H
#define L0SAMPLER_ONESPARSERECOVERYBASE_H

#include "../../../pch/common.pch"

struct OneSparseRecoveryBase
{
    void update(Int index, Int value);

    pair<Int, Int> query();
};


#endif //L0SAMPLER_ONESPARSERECOVERYBASE_H
