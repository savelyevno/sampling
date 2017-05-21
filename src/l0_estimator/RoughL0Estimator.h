//
// Created by nikita on 21.05.17.
//

#ifndef L0SAMPLER_ROUGHL0ESTIMATOR_H
#define L0SAMPLER_ROUGHL0ESTIMATOR_H

#include "../base_class/BaseClass.h"
#include "../../pch/common.pch"
#include "../hash/Hash.h"
#include "../Tools.h"

struct RoughL0EstimatorLevel;

struct RoughL0Estimator : BaseClass
{
    Int n;
    int levels;
    Hash* bucket_hash;
    Hash* level_hash;
    RoughL0EstimatorLevel** level_estimators;

    RoughL0Estimator(Random* random, PrimeGetter* prime_getter, Int _n);

    void update(Int index, Int value);

    Int query();


};


struct RoughL0EstimatorLevel : BaseClass
{
    int **buckets, eta, *non_zero_buckets, *p;
    Hash* hash;

    RoughL0EstimatorLevel(Hash* _hash, Random* random, PrimeGetter* prime_getter, int c, int _eta);

    void update(Int index, Int value);

    Int query();
};


#endif //L0SAMPLER_ROUGHL0ESTIMATOR_H
