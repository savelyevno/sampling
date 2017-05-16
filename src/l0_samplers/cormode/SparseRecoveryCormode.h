//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_SPARSERECOVERYCORMODE_H
#define L0SAMPLER_SPARSERECOVERYCORMODE_H

#include "../../../pch/common.pch"
#include "../base_classes/SparseRecoveryBase.h"
#include "../../random/Random.h"
#include "../../primes/PrimeGetter.h"

struct SparseRecoveryCormode : SparseRecoveryBase
{
    Int n, s, columns, rows;
    double delta;


    SparseRecoveryCormode(Random *_random,
                          PrimeGetter *_prime_getter,
                          Int _n,
                          Int _s,
                          double delta,
                          double one_sp_rec_err_prob);

    void update(Int index, Int value);

    set <pair <Int, Int> > query();
};


#endif //L0SAMPLER_SPARSERECOVERYCORMODE_H
