//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_ONESPARSERECOVERYBASE_H
#define L0SAMPLER_ONESPARSERECOVERYBASE_H

#include "../../../pch/common.pch"
#include "../../base_class/BaseClass.h"

struct OneSparseRecoveryBase : BaseClass
{
    virtual void update(Int index, Int value)=0;

    virtual pair<Int, Int> query()=0;
};


#endif //L0SAMPLER_ONESPARSERECOVERYBASE_H
