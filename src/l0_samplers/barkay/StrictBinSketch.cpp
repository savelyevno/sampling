//
// Created by nikita on 23.05.17.
//

#include "StrictBinSketch.h"


StrictBinSketch::StrictBinSketch()
{
    X = Y = Z = 0;

    inc_memory(sizeof(X) + sizeof(Y) + sizeof(Z));
}


void StrictBinSketch::update(Int index, Int value)
{
    X += value;
    Y += (index + 1)*value;
    Z += value*(index + 1)*(index + 1);
}

pair <Int, Int> StrictBinSketch::query()
{
    if (X > 0 && Y > 0 && Z > 0 && X*Z == Y*Y)
        return {Y/X - 1, X};
    return {-1, -1};
};




OneSparseRecoveryBase* StrictBinSketchInitializer::init_one_sp_rec(int row, Int hash_value)
{
    return new StrictBinSketch();
}