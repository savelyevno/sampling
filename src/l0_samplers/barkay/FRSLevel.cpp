//
// Created by nikita on 23.05.17.
//

#include "FRSLevel.h"


FRSLevel::FRSLevel(Hash* _hash, Int _rows, Int _columns) : columns(_columns), rows(_rows)
{
    hash = _hash;

    inc_memory(sizeof(hash) + sizeof(rows) + sizeof(columns) + sizeof(one_sparse_recoverers) +
               sizeof(one_sp_rec_initialiser));
}

void FRSLevel::update(Int index, Int value)
{
    for (int row = 0; row < rows; row++)
    {
        Int hash_value = hash->eval_hash_function(row, index);
        if (one_sparse_recoverers.count({Int(row), hash_value}) == 0)
        {
            one_sparse_recoverers[{Int(row), hash_value}] = one_sp_rec_initialiser->init_one_sp_rec(row, hash_value);
            inc_memory(one_sparse_recoverers[{Int(row), hash_value}]->get_memory());
        }
        one_sparse_recoverers[{Int(row), hash_value}]->update(index, value);
    }
}


Set <pair <Int, Int> > FRSLevel::query()
{
    Set <pair <Int, Int> > result;
    for (auto one_sparse_recoverer: one_sparse_recoverers)
    {
        auto query_result = one_sparse_recoverer.second->query();
        if (query_result.first >= 0)
            result.insert(query_result);
    }

    return result;
};





FRSLevel_StrictBinSketch::FRSLevel_StrictBinSketch(Hash* _hash, Int _rows, Int _columns) :
        FRSLevel(_hash, _rows, _columns)
{
    one_sp_rec_initialiser = new StrictBinSketchInitializer();
    inc_memory(one_sp_rec_initialiser->get_memory());
}




FRSLevel_BinSketch::FRSLevel_BinSketch(
        Hash* _hash,
        Random *_random,
        PrimeGetter *_prime_getter,
        Int n,
        int t,
        double one_sp_rec_err_prob,
        Int rows,
        Int columns) :
        FRSLevel(_hash, rows, columns)
{
    one_sp_rec_initialiser = new  BinSketchInitialiser(_random,
                                                       _prime_getter,
                                                       n,
                                                       t,
                                                       one_sp_rec_err_prob,
                                                       rows,
                                                       columns);
    inc_memory(one_sp_rec_initialiser->get_memory());
}





FRSLevel_OneSparseRecoveryCormode::FRSLevel_OneSparseRecoveryCormode(
        Hash* _hash,
        Random *_random,
        PrimeGetter *_prime_getter,
        Int n,
        double one_sp_rec_err_prob,
        Int rows,
        Int columns) :
        FRSLevel(_hash, rows, columns)
{
    one_sp_rec_initialiser = new OneSparseRecoveryCormodeInitialiser(_random,
                                                                     _prime_getter,
                                                                     n,
                                                                     one_sp_rec_err_prob,
                                                                     rows,
                                                                     columns);
    inc_memory(one_sp_rec_initialiser->get_memory());
}