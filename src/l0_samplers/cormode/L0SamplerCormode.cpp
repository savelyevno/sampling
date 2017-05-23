//
// Created by nikita on 23.05.17.
//

#include "L0SamplerCormode.h"


L0SamplerCormodeBase::L0SamplerCormodeBase(
        PrimeGetter* _prime_getter,
        Int _n,
        int _s,
        int _k,
        int init_seed
) : n(_n), s(_s)
{
    if (init_seed == 0)
        random = new Random();
    else
        random = new Random(init_seed);

    levels = Log2(n) + 1;

//        s = int(ceil(2*log2(1/delta)));
    if (_k == -1)
        k = s/2;
    else
        k = _k;

    level_hash = new Hash(_prime_getter, random, k, n, n);
    level_hash->create_hash_function();
    inc_memory(level_hash->get_memory());

    sparse_recoverers = new SparseRecoveryBase*[levels];

    cnt_lvl.resize(size_t(levels));


    inc_memory(sizeof(n) + sizeof(levels) + sizeof(k) + sizeof(sparse_recoverers) + sizeof(level_hash) +
               sizeof(s) + sizeof(random));
}


void L0SamplerCormodeBase::update(Int index, Int value)
{
    Int hash = level_hash->eval_hash_function(0, index),
            x = n;
    int level = 0;

    while (x >= hash)
    {
        sparse_recoverers[level]->update(index, value);
        cnt_lvl[level]++;
        if (x == 0)
            x = -1;
        else
            x >>= 1;
        level++;
    }
}


Set < pair<Int, Int> > L0SamplerCormodeBase::query()
{
    Set <pair <Int, Int> > result;

    for (int level = 0; level < levels; level++)
    {
        auto level_result = sparse_recoverers[level]->query();

        Int old_size = Int(result.size());

        result.insert(level_result.begin(), level_result.end());
    }

    return result;
}


ll L0SamplerCormodeBase::get_memory()
{
    ll result = memory_used;
    for (int level = 0; level < levels; level++)
    {
        result += sparse_recoverers[level]->get_memory();
    }
    return result;
}




L0SamplerCormode_SparseRecoveryCormode_OneSparseRecoveryCormode::L0SamplerCormode_SparseRecoveryCormode_OneSparseRecoveryCormode(
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




L0SamplerCormode_SparseRecoveryCormode_StrictBinSketch::L0SamplerCormode_SparseRecoveryCormode_StrictBinSketch(
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