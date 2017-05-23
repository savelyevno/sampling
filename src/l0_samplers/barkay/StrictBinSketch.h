//
// Created by nikita on 18.05.17.
//

#ifndef L0SAMPLER_STRICTBINSKETCH_H
#define L0SAMPLER_STRICTBINSKETCH_H

#include "../base_classes/OneSparseRecoveryBase.h"


struct StrictBinSketch : OneSparseRecoveryBase
{
    Int X, Y, Z;

    StrictBinSketch();

    void update(Int index, Int value);

    pair <Int, Int> query();
};



struct StrictBinSketchInitializer : OneSparseRecoveryInitialiserBase
{
    OneSparseRecoveryBase* init_one_sp_rec(int row, Int hash_value);
};

#endif //L0SAMPLER_BINSKETCH_H
