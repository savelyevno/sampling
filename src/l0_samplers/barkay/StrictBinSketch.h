//
// Created by nikita on 18.05.17.
//

#ifndef L0SAMPLER_STRICTBINSKETCH_H
#define L0SAMPLER_STRICTBINSKETCH_H

#include "../base_classes/OneSparseRecoveryBase.h"


struct StrictBinSketch : OneSparseRecoveryBase
{
    Int X, Y, Z;

    StrictBinSketch()
    {
        X = Y = Z = 0;

        inc_memory(sizeof(X) + sizeof(Y) + sizeof(Z));
    }

    void update(Int index, Int value)
    {
        X += value;
        Y += (index + 1)*value;
        Z += value*(index + 1)*(index + 1);
    }

    pair <Int, Int> query()
    {
        if (X > 0 && Y > 0 && Z > 0 && X*Z == Y*Y)
            return {Y/X - 1, X};
        return {-1, -1};
    };
};



struct StrictBinSketchInitializer : OneSparseRecoveryInitialiserBase
{
    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value)
    {
        return new StrictBinSketch();
    }
};

#endif //L0SAMPLER_BINSKETCH_H
