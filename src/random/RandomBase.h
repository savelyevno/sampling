//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_RANDOMBASE_H
#define L0SAMPLER_RANDOMBASE_H

#include "../../pch/common.pch"
#include "../base_class/BaseClass.h"

struct RandomBase : BaseClass
{
    virtual void seed(Int seed)=0;

    virtual Int getrandbits()=0;

    virtual Int randint(Int a, Int b)=0;
};


#endif //L0SAMPLER_RANDOMBASE_H
