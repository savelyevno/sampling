//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_ONESPARSERECOVERYCORMODE_H
#define L0SAMPLER_ONESPARSERECOVERYCORMODE_H

#include "../../../pch/common.pch"
#include "../base_classes/OneSparseRecoveryBase.h"
#include "../../random/Random.h"
#include "../../primes/PrimeGetter.h"


struct OneSparseRecoveryCormode : OneSparseRecoveryBase
{
    Int p, z, iota, phi, tau;
    Random *random;
    PrimeGetter *prime_getter;

    OneSparseRecoveryCormode(Random *_random,
                             PrimeGetter *_prime_getter,
                             Int _n,
                             double failure_probability);

    void update(Int index, Int value);

    pair<Int, Int> query();
};


#endif //L0SAMPLER_ONESPARSERECOVERYCORMODE_H
