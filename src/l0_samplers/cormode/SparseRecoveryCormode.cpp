//
// Created by nikita on 15.05.17.
//

#include "SparseRecoveryCormode.h"

SparseRecoveryCormode::SparseRecoveryCormode(Random *_random,
                                             PrimeGetter *_prime_getter,
                                             Int _n,
                                             Int _s,
                                             double _delta,
                                             double _one_sp_rec_err_prob)
{
    n = _n;
    s = _s;

    one_sp_rec_p = _prime_getter->get_next_prime(Int(n/_one_sp_rec_err_prob));

    columns = 2*s;
    rows = Int(log(s/_delta));

    hash_functions = new Hash(_prime_getter, _random, 2, n, columns);
    for (int row = 0; row < rows; row++)
        hash_functions->create_hash_function();

    z_generator = new Hash(_prime_getter, _random, 2, columns*rows, one_sp_rec_p);
    z_generator->create_hash_function();
}

void SparseRecoveryCormode::update(Int index, Int value)
{
    for (int row = 0; row < rows; row++)
    {
        Int hash_value = hash_functions->eval_hash_function(row, index);
        if (one_sparse_recoverers.count({row, hash_value}) == 0)
        {
            one_sparse_recoverers[{row, hash_value}] = new OneSparseRecovery(
                    one_sp_rec_p,
                    z_generator->eval_hash_function(0, row*rows + hash_value)
            );
        }

        one_sparse_recoverers[{row, hash_value}]->update(index, value);
    }
}

Set <pair<Int, Int>> SparseRecoveryCormode::query()
{
    Set <pair <Int, Int> > result;
    for (auto one_sparse_recoverer: one_sparse_recoverers)
        result.insert(one_sparse_recoverer.second->query());

    return result;
}

