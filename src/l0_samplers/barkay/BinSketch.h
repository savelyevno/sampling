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
        return {-1, -1};
    };
};

#endif //L0SAMPLER_BINSKETCH_H
