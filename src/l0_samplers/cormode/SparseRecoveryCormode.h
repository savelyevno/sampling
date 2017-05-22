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
    Int rows, columns;
    Hash* hash_functions;
    Map <std::pair<Int, Int>, OneSparseRecoveryBase*> one_sparse_recoverers;
    OneSparseRecoveryInitialiserBase* one_sp_rec_initialiser;

    SparseRecoveryCormodeBase(Random *_random,
                              PrimeGetter *_prime_getter,
                              Int n,
                              int s,
                              double delta)
    {
        columns = 2*s;
        rows = Int(log(s/delta));

        hash_functions = new Hash(_prime_getter, _random, 2, n, columns);
        for (int row = 0; row < rows; row++)
            hash_functions->create_hash_function();
        inc_memory(hash_functions->get_memory());


        inc_memory(sizeof(rows) + sizeof(columns) + sizeof(hash_functions) + sizeof(one_sparse_recoverers) +
            sizeof(one_sp_rec_initialiser));
    }


    void update(Int index, Int value)
    {
        for (int row = 0; row < rows; row++)
        {
            Int hash_value = hash_functions->eval_hash_function(row, index);
            if (one_sparse_recoverers.count({row, hash_value}) == 0)
            {
                one_sparse_recoverers[{row, hash_value}] = one_sp_rec_initialiser->init_one_sp_rec(row, hash_value);
                SparseRecoveryCormodeBase::inc_memory(one_sparse_recoverers[{row, hash_value}]->get_memory());

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
    SparseRecoveryCormode_OneSparseRecoveryCormode(Random *_random,
                                                   PrimeGetter *_prime_getter,
                                                   Int n,
                                                   int _s,
                                                   double delta,
                                                   double one_sp_rec_err_prob) :
            SparseRecoveryCormodeBase(_random,
                                      _prime_getter,
                                       n,
                                      _s,
                                      delta)
    {
        one_sp_rec_initialiser = new OneSparseRecoveryCormodeInitialiser(_random,
                                                                         _prime_getter,
                                                                         n,
                                                                         one_sp_rec_err_prob,
                                                                         this->rows,
                                                                         this->columns
        );
        inc_memory(one_sp_rec_initialiser->get_memory());
    }
};



struct SparseRecoveryCormode_StrictBinSketch : SparseRecoveryCormodeBase
{
    SparseRecoveryCormode_StrictBinSketch(Random *_random,
                                          PrimeGetter *_prime_getter,
                                          Int _n,
                                          int _s,
                                          double delta) :
            SparseRecoveryCormodeBase(_random,
                                      _prime_getter,
                                      _n,
                                      _s,
                                      delta)
    {
        one_sp_rec_initialiser = new StrictBinSketchInitializer();
        inc_memory(one_sp_rec_initialiser->get_memory());
    }
};



struct SparseRecoveryCormode_BinSketch : SparseRecoveryCormodeBase
{
    SparseRecoveryCormode_BinSketch(Random *_random,
                                          PrimeGetter *_prime_getter,
                                          Int n,
                                          int _s,
                                          double delta,
                                          double one_sp_rec_err_prob,
                                          int t) :
            SparseRecoveryCormodeBase(_random,
                                      _prime_getter,
                                      n,
                                      _s,
                                      delta)
    {
        one_sp_rec_initialiser = new BinSketchInitialiser(
                _random,
                _prime_getter,
                n,
                t,//t
                one_sp_rec_err_prob,
                rows,
                columns
        );
        inc_memory(one_sp_rec_initialiser->get_memory());
    }
};

#endif //L0SAMPLER_SPARSERECOVERYCORMODE_H
