//
// Created by nikita on 23.05.17.
//

#include "SparseRecoveryCormode.h"


SparseRecoveryCormodeBase::SparseRecoveryCormodeBase(
        Random *_random,
        PrimeGetter *_prime_getter,
        Int n,
        int s,
        double delta
)
{
//        columns = 2*s;
    columns = s/4;
    rows = Int(Log2(Int(s/delta)));
//        rows = Int(log(s/delta));

    hash_functions = new Hash(_prime_getter, _random, 2, n, columns);
    for (int row = 0; row < rows; row++)
        hash_functions->create_hash_function();
    inc_memory(hash_functions->get_memory());


    inc_memory(sizeof(rows) + sizeof(columns) + sizeof(hash_functions) + sizeof(one_sparse_recoverers) +
               sizeof(one_sp_rec_initialiser));
}


void SparseRecoveryCormodeBase::update(Int index, Int value)
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

Set <pair <Int, Int> > SparseRecoveryCormodeBase::query()
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





SparseRecoveryCormode_OneSparseRecoveryCormode::SparseRecoveryCormode_OneSparseRecoveryCormode(
        Random *_random,
        PrimeGetter *_prime_getter,
        Int n,
        int _s,
        double delta,
        double one_sp_rec_err_prob
) :
        SparseRecoveryCormodeBase(
                _random,
                _prime_getter,
                n,
                _s,
                delta
        )
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





SparseRecoveryCormode_StrictBinSketch::SparseRecoveryCormode_StrictBinSketch(
        Random *_random,
        PrimeGetter *_prime_getter,
        Int _n,
        int _s,
        double delta
) :
        SparseRecoveryCormodeBase(
                _random,
                _prime_getter,
                _n,
                _s,
                delta
        )
{
    one_sp_rec_initialiser = new StrictBinSketchInitializer();
    inc_memory(one_sp_rec_initialiser->get_memory());
}





SparseRecoveryCormode_BinSketch::SparseRecoveryCormode_BinSketch(
        Random *_random,
        PrimeGetter *_prime_getter,
        Int n,
        int _s,
        double delta,
        double one_sp_rec_err_prob,
        int t
) :
        SparseRecoveryCormodeBase(
                _random,
                _prime_getter,
                n,
                _s,
                delta
        )
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