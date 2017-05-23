//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_L0SAMPLERCORMODE_H
#define L0SAMPLER_L0SAMPLERCORMODE_H


#include "../base_classes/L0SamplerBase.h"
#include "../../primes/PrimeGetter.h"
#include "../../hash/Hash.h"
#include "../../base_class/BaseClass.h"
#include "../base_classes/SparseRecoveryBase.h"
#include "SparseRecoveryCormode.h"
#include "../barkay/FRS.h"


struct L0SamplerCormodeBase : L0SamplerBase
{
    int k, levels, s;
    Int n;
    Hash* level_hash;
    Random* random;
    SparseRecoveryBase** sparse_recoverers;
    vector <int> cnt_lvl;

    L0SamplerCormodeBase(
            PrimeGetter* _prime_getter,
            Int _n,
            int _s,
            int _k,
            int init_seed
    );

    void update(Int index, Int value);

    Set < pair<Int, Int> > query();

    ll get_memory();
};



struct L0SamplerCormode_SparseRecoveryCormode_OneSparseRecoveryCormode : L0SamplerCormodeBase
{
    L0SamplerCormode_SparseRecoveryCormode_OneSparseRecoveryCormode(
            PrimeGetter* _prime_getter,
            Int _n,
            int s,
            double sp_rec_delta,
            double one_sp_rec_err_prob,
            int _k,
            int init_seed
    );
};



struct L0SamplerCormode_SparseRecoveryCormode_StrictBinSketch : L0SamplerCormodeBase
{
    L0SamplerCormode_SparseRecoveryCormode_StrictBinSketch(
            PrimeGetter* _prime_getter,
            Int _n,
            int s,
            double sp_rec_delta,
            double one_sp_rec_err_prob,
            int _k,
            int init_seed
    );
};



struct L0SamplerCormode_SparseRecoveryCormode_BinSketch : L0SamplerCormodeBase
{
    L0SamplerCormode_SparseRecoveryCormode_BinSketch(
            PrimeGetter* _prime_getter,
            Int _n,
            int s,
            double sp_rec_delta,
            double one_sp_rec_err_prob,
            int _k,
            int init_seed
    ):
            L0SamplerCormodeBase(
                    _prime_getter,
                    _n,
                    s,
                    _k,
                    init_seed
            )
    {
        for (int level = 0; level < levels; level++)
        {
            sparse_recoverers[level] = new SparseRecoveryCormode_BinSketch(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta,
                    one_sp_rec_err_prob,
                    10   //t
            );
            inc_memory(sizeof(sparse_recoverers[level]));
        }
    }
};






#endif //L0SAMPLER_L0SAMPLERCORMODE_H
