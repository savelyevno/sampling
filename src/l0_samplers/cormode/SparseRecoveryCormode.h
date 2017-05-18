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


template <class OneSpRecClass>
struct SparseRecoveryCormode : SparseRecoveryBase
{
    Int n, s, columns, rows, one_sp_rec_p;
    Hash* hash_functions;
    Hash* z_generator;
    Map <std::pair<Int, Int>, OneSpRecClass*> one_sparse_recoverers;

    SparseRecoveryCormode(Random *_random,
                          PrimeGetter *_prime_getter,
                          Int _n,
                          Int _s,
                          double _delta,
                          double _one_sp_rec_err_prob)
    {
        inc_memory(sizeof(n) + sizeof(s) + sizeof(columns) + sizeof(rows) + sizeof(one_sp_rec_p));

        n = _n;
        s = _s;

        one_sp_rec_p = _prime_getter->get_next_prime(Int(n/_one_sp_rec_err_prob));

        columns = 2*s;
        rows = Int(log(s/_delta));

        hash_functions = new Hash(_prime_getter, _random, 2, n, columns);
        for (int row = 0; row < rows; row++)
            hash_functions->create_hash_function();
        inc_memory(hash_functions->get_memory());

        z_generator = new Hash(_prime_getter, _random, 2, columns*rows, one_sp_rec_p);
        z_generator->create_hash_function();
        inc_memory(z_generator->get_memory());
    }


    void update(Int index, Int value)
    {
        for (int row = 0; row < rows; row++)
        {
            Int hash_value = hash_functions->eval_hash_function(row, index);
            if (one_sparse_recoverers.count({row, hash_value}) == 0)
            {
                one_sparse_recoverers[{row, hash_value}] = new OneSpRecClass(
                        one_sp_rec_p,
                        z_generator->eval_hash_function(0, row*rows + hash_value)
                );
                inc_memory(one_sparse_recoverers[{row, hash_value}]->get_memory());
            }

            one_sparse_recoverers[{row, hash_value}]->update(index, value);
        }
    }


    Set <pair <Int, Int> > query()
    {
        Set <pair <Int, Int> > result;
        for (auto one_sparse_recoverer: one_sparse_recoverers)
        {
            auto query_result = one_sparse_recoverer.second->query();
            if (query_result.first >= 0)
                result.insert(query_result);
        }

        return result;
    }

};


#endif //L0SAMPLER_SPARSERECOVERYCORMODE_H
