//
// Created by nikita on 20.05.17.
//

#ifndef L0SAMPLER_BINSKETCH_H
#define L0SAMPLER_BINSKETCH_H

#include "../base_classes/OneSparseRecoveryBase.h"
#include "../../hash/Hash.h"

struct BinSketch : OneSparseRecoveryBase
{
    Int X, Y, Z, T;
    Hash* hash_object;
    int hash_f_id;

    BinSketch(int _hash_f_id, Hash* _hash_object);

    void update(Int index, Int value);

    pair <Int, Int> query();
};



struct BinSketchInitialiser : OneSparseRecoveryInitialiserBase
{
    Hash* bin_sketch_hash;
    Hash* seed_generator;
    Int bin_sketch_hash_image_size, rows;
    Random* random;

    BinSketchInitialiser(
            Random *_random,
            PrimeGetter *_prime_getter,
            Int n,
            int t,
            double one_sp_rec_err_prob,
            Int _rows,
            Int columns
    );

    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value);
};


#endif //L0SAMPLER_BINSKETCH_H
