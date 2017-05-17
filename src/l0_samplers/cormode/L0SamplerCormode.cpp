//
// Created by nikita on 17.05.17.
//

#include "L0SamplerCormode.h"

L0SamplerCormode::L0SamplerCormode(PrimeGetter* _prime_getter,
                                   Int _n,
                                   double eps,
                                   double delta,
                                   double sp_rec_delta,
                                   double one_sp_rec_err_prob,
                                   double _hash_level_n_power,
                                   Int _k,
                                   Int init_seed)
{
    Random* random;
    if (init_seed == 0)
        random = new Random();
    else
        random = new Random(init_seed);

    n = _n;

    levels = Int(ceil(log2(n)));

    Int s = Int(ceil(log2(1/delta)) + ceil(log2(1/eps)));
    if (_k == -1)
        k = 2*s;
    else
        k = _k;

    hash_level_domain_size = Int(pow(n, _hash_level_n_power));
    level_hash = new Hash(_prime_getter, random, k, n, hash_level_domain_size);
    level_hash->create_hash_function();

    sparse_recoverers = new SparseRecovery*[levels];
    for (int level = 0; level < levels; level++)
        sparse_recoverers[level] = new SparseRecovery(
                random,
                _prime_getter,
                n,
                s,
                sp_rec_delta,
                one_sp_rec_err_prob
        );
}

void L0SamplerCormode::update(Int index, Int value)
{
    Int hash = level_hash->eval_hash_function(0, index),
        x = hash_level_domain_size, level = 0;

    while (x >= hash)
    {
        sparse_recoverers[level]->update(index, value);

        x >>= 1;
        level++;
    }
}

Set <pair<Int, Int>> L0SamplerCormode::query()
{
    Set <pair <Int, Int> > result;

    for (int level = 0; level < levels; level++)
    {
        auto level_result = sparse_recoverers[level]->query();
        result.insert(level_result.begin(), level_result.end());
    }

    return result;
}
