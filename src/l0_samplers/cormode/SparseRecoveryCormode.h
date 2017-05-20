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
    Int n, columns, rows, one_sp_rec_p;
    int s;
    Hash* hash_functions;
    Map <std::pair<Int, Int>, OneSparseRecoveryBase*> one_sparse_recoverers;

    SparseRecoveryCormodeBase(Random *_random,
                              PrimeGetter *_prime_getter,
                              Int _n,
                              int _s,
                              double _delta)
    {
        inc_memory(sizeof(n) + sizeof(s) + sizeof(columns) + sizeof(rows));

        n = _n;
        s = _s;

        columns = 2*s;
        rows = Int(log(s/_delta));

        hash_functions = new Hash(_prime_getter, _random, 2, n, columns);
        for (int row = 0; row < rows; row++)
            hash_functions->create_hash_function();
        inc_memory(hash_functions->get_memory());
    }

    virtual OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value) = 0;

    void update(Int index, Int value)
    {
        for (int row = 0; row < rows; row++)
        {
            Int hash_value = hash_functions->eval_hash_function(row, index);
            if (one_sparse_recoverers.count({row, hash_value}) == 0)
            {
                one_sparse_recoverers[{row, hash_value}] = init_one_sp_rec(row, hash_value);
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


struct SparseRecoveryCormode_OneSparseRecoveryCormode : SparseRecoveryCormodeBase
{
    Hash* z_generator;

    SparseRecoveryCormode_OneSparseRecoveryCormode(Random *_random,
                                                   PrimeGetter *_prime_getter,
                                                   Int _n,
                                                   int _s,
                                                   double _delta,
                                                   double _one_sp_rec_err_prob) :
            SparseRecoveryCormodeBase(_random,
                                      _prime_getter,
                                       _n,
                                      _s,
                                      _delta)
    {
        one_sp_rec_p = _prime_getter->get_next_prime(n*Int(1/_one_sp_rec_err_prob));
        inc_memory(sizeof(one_sp_rec_p));

        z_generator = new Hash(_prime_getter, _random, 2, columns*rows, one_sp_rec_p);
        z_generator->create_hash_function();
        inc_memory(z_generator->get_memory());
    }

    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value)
    {
        return new OneSparseRecoveryCormode(
                z_generator->eval_hash_function(
                        0,
                        row*rows + hash_value
                ),
                one_sp_rec_p
        );
    }
};

struct SparseRecoveryCormode_StrictBinSketch : SparseRecoveryCormodeBase
{
    SparseRecoveryCormode_StrictBinSketch(Random *_random,
                                                   PrimeGetter *_prime_getter,
                                                   Int _n,
                                                   int _s,
                                                   double _delta,
                                                   double _one_sp_rec_err_prob) :
            SparseRecoveryCormodeBase(_random,
                                      _prime_getter,
                                      _n,
                                      _s,
                                      _delta)
    {

    }

    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value)
    {
        return new StrictBinSketch();
    }
};


struct SparseRecoveryCormode_BinSketch : SparseRecoveryCormodeBase
{
    Hash* bin_sketch_hash;
    Hash* seed_generator;
    Int bin_sketch_hash_image_size;
    Random* random;

    SparseRecoveryCormode_BinSketch(Random *_random,
                                          PrimeGetter *_prime_getter,
                                          Int _n,
                                          int _s,
                                          double _delta,
                                          double _one_sp_rec_err_prob) :
            SparseRecoveryCormodeBase(_random,
                                      _prime_getter,
                                      _n,
                                      _s,
                                      _delta)
    {
        bin_sketch_hash_image_size = Int(1/_one_sp_rec_err_prob);

        random = new Random();

        int t = 10;
        bin_sketch_hash = new Hash(_prime_getter, random, t, n + 1, bin_sketch_hash_image_size);
        inc_memory(bin_sketch_hash->get_memory());

        inc_memory(sizeof(bin_sketch_hash_image_size) +
            sizeof(bin_sketch_hash) + sizeof(random) + sizeof(seed_generator));

        seed_generator = new Hash(_prime_getter, _random, t, rows*columns, Int(1) << 30);
        seed_generator->create_hash_function();
        inc_memory(seed_generator->get_memory());
    }

    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value)
    {
        int seed;
        #ifdef BOOST
            seed = (seed_generator->eval_hash_function(0, row*rows + hash_value)).convert_to<int>();
        #else
            seed = int(seed_generator->eval_hash_function(0, row*rows + hash_value));
        #endif

        memory_used -= bin_sketch_hash->get_memory();

        random->seed(seed);
        auto result = new BinSketch(bin_sketch_hash->create_hash_function(), bin_sketch_hash);

        memory_used += bin_sketch_hash->get_memory();

        return result;
    }
};

#endif //L0SAMPLER_SPARSERECOVERYCORMODE_H
