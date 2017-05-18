//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_PRIMEGETTER_H
#define L0SAMPLER_PRIMEGETTER_H

#include "../../pch/common.pch"
#include "../random/Random.h"
#include "../Tools.h"

struct PrimeGetter : BaseClass
{
    unordered_map<Int, Int> cache;
    Random *random;

    PrimeGetter(Random *_random);

    //O(log(n)^3)
    bool is_prime(Int n);

    //almost O(log(n)^3)
    Int get_next_prime(Int n);
};


#endif //L0SAMPLER_PRIMEGETTER_H
