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

    BinSketch(int _hash_f_id, Hash* _hash_object) : hash_f_id(_hash_f_id), hash_object(_hash_object)
    {
        X = Y = Z = T = 0;

        inc_memory(sizeof(X) + sizeof(Y) + sizeof(Z) + sizeof(T) + sizeof(hash_f_id) +
            sizeof(hash_object));
    }

    void update(Int index, Int value)
    {
        X += value;
        Y += (index + 1)*value;
        Z += value*(index + 1)*(index + 1);

        T += value*hash_object->eval_hash_function(hash_f_id, index + 1);
    }

    pair <Int, Int> query()
    {
        if (X > 0 && Y > 0 && Z > 0 && X*Z == Y*Y && X*hash_object->eval_hash_function(hash_f_id, Y/X) == T)
            return {Y/X - 1, X};
        return {Int(-1), Int(-1)};
    };
};



struct BinSketchInitialiser : OneSparseRecoveryInitialiserBase
{
    Hash* bin_sketch_hash;
    Hash* seed_generator;
    Int bin_sketch_hash_image_size, rows;
    Random* random;

    BinSketchInitialiser(Random *_random,
                         PrimeGetter *_prime_getter,
                         Int n,
                         int t,
                         double one_sp_rec_err_prob,
                         Int _rows,
                         Int columns
    ) : rows(_rows)
    {
        bin_sketch_hash_image_size = Int(1/one_sp_rec_err_prob);

        random = new Random();

        bin_sketch_hash = new Hash(_prime_getter, random, t, n + 1, bin_sketch_hash_image_size);
        inc_memory(bin_sketch_hash->get_memory());

        seed_generator = new Hash(_prime_getter, _random, t, rows*columns, Int(1) << 30);
        seed_generator->create_hash_function();
        inc_memory(seed_generator->get_memory());


        inc_memory(sizeof(bin_sketch_hash_image_size) + sizeof(rows) +
                   sizeof(bin_sketch_hash) + sizeof(random) + sizeof(seed_generator));
    }

    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value)
    {
        int seed = convert_to_int(seed_generator->eval_hash_function(0, row*rows + hash_value));

        memory_used -= bin_sketch_hash->get_memory();

        random->seed(seed);
        auto result = new BinSketch(bin_sketch_hash->create_hash_function(), bin_sketch_hash);

        memory_used += bin_sketch_hash->get_memory();

        return result;
    }
};


#endif //L0SAMPLER_BINSKETCH_H
