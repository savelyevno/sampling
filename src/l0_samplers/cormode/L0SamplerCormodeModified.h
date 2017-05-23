//
// Created by nikita on 23.05.17.
//

#ifndef L0SAMPLER_L0SAMPLERCORMODEMODIFIED_H
#define L0SAMPLER_L0SAMPLERCORMODEMODIFIED_H


#include "L0SamplerCormode.h"


struct L0SamplerCormodeModifiedBase : L0SamplerCormodeBase
{
    Hash* level_hash;

    L0SamplerCormodeModifiedBase(
            PrimeGetter* _prime_getter,
            Int _n,
            int s,
            int _k,
            int init_seed
    );

    void update(Int index, Int value);
};



struct L0SamplerCormodeModified_SparseRecoveryCormode_OneSparseRecoveryCormode : L0SamplerCormodeModifiedBase
{
    L0SamplerCormodeModified_SparseRecoveryCormode_OneSparseRecoveryCormode(
            PrimeGetter* _prime_getter,
            Int _n,
            int s,
            double sp_rec_delta,
            double one_sp_rec_err_prob,
            int _k,
            int init_seed
    );
};



struct L0SamplerCormodeModified_SparseRecoveryCormode_StrictBinSketch : L0SamplerCormodeModifiedBase
{
    L0SamplerCormodeModified_SparseRecoveryCormode_StrictBinSketch(
            PrimeGetter* _prime_getter,
            Int _n,
            int s,
            double sp_rec_delta,
            double one_sp_rec_err_prob,
            int _k,
            int init_seed
    );
};



struct L0SamplerCormodeModified_SparseRecoveryCormode_BinSketch : L0SamplerCormodeModifiedBase
{
    L0SamplerCormodeModified_SparseRecoveryCormode_BinSketch(
            PrimeGetter* _prime_getter,
            Int _n,
            int s,
            double sp_rec_delta,
            double one_sp_rec_err_prob,
            int _k,
            int init_seed
    );
};




#endif //L0SAMPLER_L0SAMPLERCORMODEMODIFIED_H
