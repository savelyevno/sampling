//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_RANDOMBASE_H
#define L0SAMPLER_RANDOMBASE_H

#include "../../pch/common.pch"

struct RandomBase
{
    void seed(Int seed);

    Int getrandbits();

    Int randint(Int a, Int b);
};


#endif //L0SAMPLER_RANDOMBASE_H
