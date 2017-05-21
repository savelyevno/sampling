//
// Created by nikita on 21.05.17.
//

#ifndef L0SAMPLER_L0ESTIMATOR_H
#define L0SAMPLER_L0ESTIMATOR_H


#include "../primes/PrimeGetter.h"
#include "RoughL0Estimator.h"

struct L0Estimator : BaseClass
{
    RoughL0Estimator* rough_l0_estimator;
    Hash* hash1;
    Hash* hash2;
    Hash* hash3;
    Int* A, K, n;

    L0Estimator(PrimeGetter* prime_getter, Random* random, Int _n, double eps);

    void update(Int index, Int value);

    Int query();
};


#endif //L0SAMPLER_L0ESTIMATOR_H
