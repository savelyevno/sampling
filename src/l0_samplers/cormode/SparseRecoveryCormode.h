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
#include "../../base_class/BaseClass.h"
#include "../base_classes/OneSparseRecoveryBase.h"
#include "OneSparseRecoveryCormode.h"
#include "../barkay/StrictBinSketch.h"
#include "../barkay/BinSketch.h"


struct SparseRecoveryCormodeBase : SparseRecoveryBase
{
    Int rows, columns;
    Hash* hash_functions;
    Map <std::pair<Int, Int>, OneSparseRecoveryBase*> one_sparse_recoverers;
    OneSparseRecoveryInitialiserBase* one_sp_rec_initialiser;

    SparseRecoveryCormodeBase(
            Random *_random,
            PrimeGetter *_prime_getter,
            Int n,
            int s,
            double delta
    );


    void update(Int index, Int value);

    Set <pair <Int, Int> > query();

};



struct SparseRecoveryCormode_OneSparseRecoveryCormode : SparseRecoveryCormodeBase
{
    SparseRecoveryCormode_OneSparseRecoveryCormode(
            Random *_random,
            PrimeGetter *_prime_getter,
            Int n,
            int _s,
            double delta,
            double one_sp_rec_err_prob
    );
};



struct SparseRecoveryCormode_StrictBinSketch : SparseRecoveryCormodeBase
{
    SparseRecoveryCormode_StrictBinSketch(
            Random *_random,
            PrimeGetter *_prime_getter,
            Int _n,
            int _s,
            double delta
    );
};



struct SparseRecoveryCormode_BinSketch : SparseRecoveryCormodeBase
{
    SparseRecoveryCormode_BinSketch(
            Random *_random,
            PrimeGetter *_prime_getter,
            Int n,
            int _s,
            double delta,
            double one_sp_rec_err_prob,
            int t
    );
};

#endif //L0SAMPLER_SPARSERECOVERYCORMODE_H
