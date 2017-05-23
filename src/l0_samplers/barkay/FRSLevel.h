//
// Created by nikita on 23.05.17.
//

#ifndef L0SAMPLER_FRSLEVEL_H
#define L0SAMPLER_FRSLEVEL_H


#include "../../base_class/BaseClass.h"
#include "../../../pch/common.pch"
#include "../../Tools.h"
#include "../base_classes/OneSparseRecoveryBase.h"
#include "StrictBinSketch.h"
#include "../../hash/Hash.h"
#include "../base_classes/SparseRecoveryBase.h"
#include "BinSketch.h"
#include "../cormode/OneSparseRecoveryCormode.h"


struct FRSLevel : SparseRecoveryBase
{
    Int rows, columns;
    Map <pair<Int, Int>, OneSparseRecoveryBase*> one_sparse_recoverers;
    Hash* hash;
    OneSparseRecoveryInitialiserBase* one_sp_rec_initialiser;

    FRSLevel(Hash* _hash, Int _rows, Int _columns);

    void update(Int index, Int value);


    Set <pair <Int, Int> > query();
};



struct FRSLevel_StrictBinSketch : FRSLevel
{
    FRSLevel_StrictBinSketch(Hash* _hash, Int _rows, Int _columns);
};




struct FRSLevel_BinSketch: FRSLevel
{
    FRSLevel_BinSketch(
            Hash* _hash,
            Random *_random,
            PrimeGetter *_prime_getter,
            Int n,
            int t,
            double one_sp_rec_err_prob,
            Int rows,
            Int columns);
};



struct FRSLevel_OneSparseRecoveryCormode : FRSLevel
{
    FRSLevel_OneSparseRecoveryCormode(
            Hash* _hash,
            Random *_random,
            PrimeGetter *_prime_getter,
            Int n,
            double one_sp_rec_err_prob,
            Int rows,
            Int columns);
};




#endif //L0SAMPLER_FRSLEVEL_H
