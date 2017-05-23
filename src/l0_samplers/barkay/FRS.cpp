//
// Created by nikita on 23.05.17.
//

#include "FRS.h"


FRSBase::FRSBase(PrimeGetter* prime_getter, Int n, int _K, double delta, int seed) : K(_K)
{
    M = 2*n;
    levels = Log2(M) + 1;
    t = Log2(Int(1/delta));

    if (seed == 0)
        random = new Random();
    else
        random = new Random(seed);


    sparse_recoverers = new SparseRecoveryBase*[convert_to_int(levels)];


    level_hash = new Hash(prime_getter, random, t, n, M);
    level_hash->create_hash_function();
    inc_memory(level_hash->get_memory());


    rows = Int(Log2(Int(K/delta)));
    columns = Int(K);
    row_hash = new Hash(prime_getter, random, 2, n, columns);
    for (int row = 0; row < rows; row++)
        row_hash->create_hash_function();
    inc_memory(row_hash->get_memory());


    l0_estimators = new L0Estimator*[t];
    for (int i = 0; i < t; i++)
    {
        l0_estimators[i] = new L0Estimator(prime_getter, random, n);
        inc_memory(sizeof(l0_estimators[i]) + l0_estimators[i]->get_memory());
    }
    l0_estimator_hash = new Hash(prime_getter, random, t, n, t);
    l0_estimator_hash->create_hash_function();
    inc_memory(l0_estimator_hash->get_memory());


    inc_memory(sizeof(levels) + sizeof(level_hash) + sizeof(row_hash) + sizeof(l0_estimators) +
               sizeof(t) + sizeof(sparse_recoverers) + sizeof(M) + sizeof(random));
}

void FRSBase::update(Int index, Int value)
{
    Int l0_estimator_hash_value = l0_estimator_hash->eval_hash_function(0, index);
    l0_estimators[convert_to_int(l0_estimator_hash_value)]->update(index, value);


    Int level_hash_value = level_hash->eval_hash_function(0, index) + 1;
    int level = 0;
    for (; level < levels; level++)
        if ((level_hash_value << (level + 1))/M != 0)
            break;

    sparse_recoverers[level]->update(index, value);
}


Int FRSBase::get_l0_etimation()
{
    vector <Int> results(t);
    for (int i = 0; i < t; i++)
        results[i] = l0_estimators[i]->query();
    sort(results.begin(), results.end());

    if (t % 2 == 0)
        return (results[(t - 1)/2] + results[t/2])*t/2;
    else
        return results[t/2]*t;
}


Set <pair <Int, Int> > FRSBase::query()
{
    Int L0_estimation = get_l0_etimation();

    int level = max(Log2(L0_estimation/K) - 2, 0);

    return sparse_recoverers[level]->query();
}

ll FRSBase::get_memory()
{
    ll result = memory_used;
    for (int level = 0; level < levels; level++)
    {
        result += sparse_recoverers[level]->get_memory();
    }
    return result;
}





FRS_FRSLevel_StrictBinSketch::FRS_FRSLevel_StrictBinSketch(
        PrimeGetter* prime_getter,
        Int n,
        int _K,
        double delta,
        int seed
) :
        FRSBase(
                prime_getter,
                n,
                _K,
                delta,
                seed)
{
    for (int level = 0; level < levels; level++)
    {
        sparse_recoverers[level] = new FRSLevel_StrictBinSketch(row_hash, rows, columns);
        inc_memory(sizeof(sparse_recoverers[level]));
    }
}




FRS_FRSLevel_BinSketch::FRS_FRSLevel_BinSketch(
        PrimeGetter* prime_getter,
        Int n,
        int _K,
        double delta,
        int seed
) :
        FRSBase(
                prime_getter,
                n,
                _K,
                delta,
                seed)
{
    for (int level = 0; level < levels; level++)
    {
        sparse_recoverers[level] = new FRSLevel_BinSketch(
                row_hash,
                random,
                prime_getter,
                n,
                t,
                1e-2,
                rows,
                columns
        );
        inc_memory(sizeof(sparse_recoverers[level]));
    }
}




FRS_FRSLevel_OneSparseRecoveryCormode::FRS_FRSLevel_OneSparseRecoveryCormode(
        PrimeGetter* prime_getter,
        Int n,
        int _K,
        double delta,
        int seed
) :
        FRSBase(
                prime_getter,
                n,
                _K,
                delta,
                seed)
{
    for (int level = 0; level < levels; level++)
    {
        sparse_recoverers[level] = new FRSLevel_OneSparseRecoveryCormode(
                row_hash,
                random,
                prime_getter,
                n,
                1e-2,
                rows,
                columns
        );
        inc_memory(sizeof(sparse_recoverers[level]));
    }
}