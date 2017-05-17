//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_L0SAMPLERCORMODE_H
#define L0SAMPLER_L0SAMPLERCORMODE_H

#include "../base_classes/L0SamplerBase.h"
#include "../../primes/PrimeGetter.h"
#include "../../hash/Hash.h"
#include "settings.h"

struct L0SamplerCormode : L0SamplerBase
{
    Int n, levels, k;
    Hash* level_hash;
    SparseRecovery** sparse_recoverers;
    Hash* tmp_hash;
    vector <int> cnt_lvl;

    L0SamplerCormode(
            PrimeGetter* _prime_getter,
            Int _n,
            double delta,
            double sp_rec_delta,
            double _one_sp_rec_err_prob,
            Int _k,
            Int init_seed
    );

    void update(Int index, Int value);

    Set < pair<Int, Int> > query();
};


#endif //L0SAMPLER_L0SAMPLERCORMODE_H
