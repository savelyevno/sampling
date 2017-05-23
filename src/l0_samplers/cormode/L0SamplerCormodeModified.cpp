//
// Created by nikita on 23.05.17.
//

#include "L0SamplerCormodeModified.h"


L0SamplerCormodeModifiedBase::L0SamplerCormodeModifiedBase(
        PrimeGetter* _prime_getter,
        Int _n,
        int s,
        int _k,
        int init_seed
) :
        L0SamplerCormodeBase(
                _prime_getter,
                _n,
                s,
                _k,
                init_seed
        )
{
    level_hash = new Hash(_prime_getter, random, k, n, n);
    for (int level = 0; level < levels; level++)
        level_hash->create_hash_function();
    inc_memory(level_hash->get_memory());
}


void L0SamplerCormodeModifiedBase::update(Int index, Int value)
{
    for (int level = 0; level < levels; level++)
    {
        Int hash = level_hash->eval_hash_function(level, index);
        if (n >> level >= hash)
        {
            cnt_lvl[level]++;
            sparse_recoverers[level]->update(index, value);
        }
    }

}






L0SamplerCormodeModified_SparseRecoveryCormode_OneSparseRecoveryCormode::L0SamplerCormodeModified_SparseRecoveryCormode_OneSparseRecoveryCormode(
        PrimeGetter* _prime_getter,
        Int _n,
        int s,
        double sp_rec_delta,
        double one_sp_rec_err_prob,
        int _k,
        int init_seed
):
        L0SamplerCormodeModifiedBase(
                _prime_getter,
                _n,
                s,
                _k,
                init_seed
        )
{
    for (int level = 0; level < levels; level++)
    {
        sparse_recoverers[level] = new SparseRecoveryCormode_OneSparseRecoveryCormode(
                random,
                _prime_getter,
                n,
                s,
                sp_rec_delta,
                one_sp_rec_err_prob
        );
        inc_memory(sizeof(sparse_recoverers[level]));
    }
}





L0SamplerCormodeModified_SparseRecoveryCormode_StrictBinSketch::L0SamplerCormodeModified_SparseRecoveryCormode_StrictBinSketch(
        PrimeGetter* _prime_getter,
        Int _n,
        int s,
        double sp_rec_delta,
        double one_sp_rec_err_prob,
        int _k,
        int init_seed
):
        L0SamplerCormodeModifiedBase(
                _prime_getter,
                _n,
                s,
                _k,
                init_seed
        )
{
    for (int level = 0; level < levels; level++)
    {
        sparse_recoverers[level] = new SparseRecoveryCormode_StrictBinSketch(
                random,
                _prime_getter,
                n,
                s,
                sp_rec_delta
        );
        inc_memory(sizeof(sparse_recoverers[level]));
    }
}





L0SamplerCormodeModified_SparseRecoveryCormode_BinSketch::L0SamplerCormodeModified_SparseRecoveryCormode_BinSketch(
        PrimeGetter* _prime_getter,
        Int _n,
        int s,
        double sp_rec_delta,
        double one_sp_rec_err_prob,
        int _k,
        int init_seed
):
        L0SamplerCormodeModifiedBase(
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