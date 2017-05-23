//
// Created by nikita on 22.05.17.
//

#ifndef L0SAMPLER_FRS_H
#define L0SAMPLER_FRS_H

#include "../../base_class/BaseClass.h"
#include "../../../pch/common.pch"
#include "../../Tools.h"
#include "../base_classes/OneSparseRecoveryBase.h"
#include "StrictBinSketch.h"
#include "../../hash/Hash.h"
#include "../../l0_estimator/L0Estimator.h"
#include "FRSLevel.h"



struct FRSBase : BaseClass
{
    Hash* level_hash;
    Hash* row_hash;
    Hash* l0_estimator_hash;
    Int levels, M, rows, columns;
    int t, K;
    L0Estimator** l0_estimators;
    SparseRecoveryBase** sparse_recoverers;
    Random* random;

    FRSBase(PrimeGetter* prime_getter, Int n, int _K, double delta, int seed);

    void update(Int index, Int value);

    Int get_l0_etimation();

    Set <pair <Int, Int> > query();

    ll get_memory();
};




struct FRS_FRSLevel_StrictBinSketch : FRSBase
{
    FRS_FRSLevel_StrictBinSketch(
            PrimeGetter* prime_getter,
            Int n,
            int _K,
            double delta,
            int seed=0
    );
};



struct FRS_FRSLevel_BinSketch : FRSBase
{
    FRS_FRSLevel_BinSketch(
            PrimeGetter* prime_getter,
            Int n,
            int _K,
            double delta,
            int seed=0
    );
};



struct FRS_FRSLevel_OneSparseRecoveryCormode : FRSBase
{
    FRS_FRSLevel_OneSparseRecoveryCormode(
            PrimeGetter* prime_getter,
            Int n,
            int _K,
            double delta,
            int seed=0
    );
};








#endif //L0SAMPLER_FRS_H
