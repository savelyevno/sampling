//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_SPARSERECOVERYCORMODE_H
#define L0SAMPLER_SPARSERECOVERYCORMODE_H

#include "../../../pch/common.pch"
#include "../base_classes/SparseRecoveryBase.h"
#include "../../random/Random.h"
#include "../../primes/PrimeGetter.h"
#include "../../hash/Hash.h"
#include "settings.h"


struct SparseRecoveryCormode : SparseRecoveryBase
{
    Int n, s, columns, rows, one_sp_rec_p;
    Hash* hash_functions;
    Hash* z_generator;
    Map <std::pair<Int, Int>, OneSparseRecoveryBase*> one_sparse_recoverers;

//    SparseRecoveryCormode(){};

    SparseRecoveryCormode(Random *_random,
                          PrimeGetter *_prime_getter,
                          Int _n,
                          Int _s,
                          double _delta,
                          double _one_sp_rec_err_prob);

    void update(Int index, Int value);

    Set <pair <Int, Int> > query();
};


#endif //L0SAMPLER_SPARSERECOVERYCORMODE_H
