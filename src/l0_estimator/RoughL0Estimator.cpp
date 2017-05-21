//
// Created by nikita on 21.05.17.
//

#include "RoughL0Estimator.h"


RoughL0Estimator::RoughL0Estimator(Random* random, PrimeGetter* prime_getter, Int _n)
{
    n = _n;
    level_hash = new Hash(prime_getter, random, 2, n, n);
    level_hash->create_hash_function();
    inc_memory(level_hash->get_memory());

    int c = 141, eta = 4;

    bucket_hash = new Hash(prime_getter, random, 2, n, c*c);
    for (int i = 0; i < eta; i++)
        bucket_hash->create_hash_function();
    inc_memory(bucket_hash->get_memory());

    levels = Log2(n) + 1;
    level_estimators = new RoughL0EstimatorLevel*[levels];
    for (int level = 0; level < levels; level++)
    {
        level_estimators[level] = new RoughL0EstimatorLevel(bucket_hash, random, prime_getter, c, eta);
        inc_memory(level_estimators[level]->get_memory() + sizeof(level_estimators[level]));
    }

    inc_memory(sizeof(level_hash) + sizeof(bucket_hash) + sizeof(level_estimators) + sizeof(levels) + sizeof(n));
}


void RoughL0Estimator::update(Int index, Int value)
{
    int lsb_value = lsb(level_hash->eval_hash_function(0, index) + 1, n);

//    for (int level = 0; level <= lsb_value; level++)
//        level_estimators[level]->update(index, value);
    level_estimators[lsb_value]->update(index, value);
}


Int RoughL0Estimator::query()
{
//    for (int level = levels - 1; level >= 0; level--)
//    {
//        cout << level << ": " << endl;
//        for (int i = 0; i < 4; i++)
//        {
//            cout << i << " " << level_estimators[level]->non_zero_buckets[i] << endl;
//        }
//        cout << "+++++++++++++++++++++++++++" << endl;
//    }

    Int result = 1;

    for (int level = levels - 1; level >=0; level--)
        if (level_estimators[level]->query() > 8)
        {
            result = Int(1) << level;
            break;
        }

    return result;
}






RoughL0EstimatorLevel::RoughL0EstimatorLevel(Hash* _hash, Random *random, PrimeGetter *prime_getter, int c, int _eta)
{
    hash = _hash;
    eta = _eta;

    Int log_value = Int(Log2(Int(MAXLEN)*MAXVAL) + 1);
    Int log_log_value = Int(Log2(log_value) + 1);
    Int p_arg_value = log_value*log_log_value;
    Int log_p_arg_value = Int(Log2(log_value*log_log_value) + 1);

    buckets = new int*[eta];
    non_zero_buckets = new int[eta];
    p = new int[eta];
    for (int i = 0; i < eta; i++)
    {
        buckets[i] = new int[c * c];
        non_zero_buckets[i] = 0;
        inc_memory(sizeof(buckets[i]));

        Int P = prime_getter->get_next_prime(p_arg_value + 2*log_p_arg_value - random->randint(0, 4*log_p_arg_value));
        assert(P < (1 << 30));

        p[i] = convert_to_int(P);
    }

    inc_memory(sizeof(eta) + sizeof(hash) + sizeof(p) + eta*sizeof(int)*(c*c* + 1 + 1) +
                       sizeof(non_zero_buckets) + sizeof(buckets));
}


void RoughL0EstimatorLevel::update(Int index, Int value)
{
    for (int i = 0; i < eta; i++)
    {
        int column = convert_to_int(hash->eval_hash_function(i, index));
        int was_zero = buckets[i][column] == 0;

        buckets[i][convert_to_int(hash->eval_hash_function(i, index))] += convert_to_int(value % p[i]);

        if (buckets[i][column] != 0 && was_zero)
            non_zero_buckets[i] += 1;
        if (buckets[i][column] == 0 && !was_zero)
            non_zero_buckets[i] -= 1;
    }
}


Int RoughL0EstimatorLevel::query()
{
    Int result = 0;

    for (int i = 0; i < eta; i++)
    {
        if (result < non_zero_buckets[i])
            result = non_zero_buckets[i];
    }

    return result;
}

