//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_ONESPARSERECOVERYCORMODE_H
#define L0SAMPLER_ONESPARSERECOVERYCORMODE_H

#include "../../../pch/common.pch"
#include "../base_classes/OneSparseRecoveryBase.h"
#include "../../random/Random.h"
#include "../../primes/PrimeGetter.h"
#include "../../base_class/BaseClass.h"
#include "../../hash/Hash.h"


struct OneSparseRecoveryCormode : OneSparseRecoveryBase
{
    Int p, z, iota, phi, tau;

    OneSparseRecoveryCormode(Int _z, Int _p);

    void update(Int index, Int value);

    pair<Int, Int> query();

};


struct OneSparseRecoveryCormodeInitialiser : OneSparseRecoveryInitialiserBase
{
    Hash* z_generator;
    Int one_sp_rec_p, rows;

    OneSparseRecoveryCormodeInitialiser(
            Random *_random,
            PrimeGetter *_prime_getter,
            Int n,
            double one_sp_rec_err_prob,
            Int _rows,
            Int columns
    );

    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value);
};



#endif //L0SAMPLER_ONESPARSERECOVERYCORMODE_H
