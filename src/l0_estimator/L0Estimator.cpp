//
// Created by nikita on 21.05.17.
//

#include "L0Estimator.h"

L0Estimator::L0Estimator(PrimeGetter *prime_getter, Random *random, Int _n)
{
    double eps = 0.1;
    n = _n;

    rough_l0_estimator = new RoughL0Estimator(random, prime_getter, n);
    inc_memory(rough_l0_estimator->get_memory());

    K = Int(1/eps/eps) + 1;

    A = new Int[convert_to_int(K)];
    for (int i = 0; i < K; i++)
        A[i] = 0;

    hash1 = new Hash(prime_getter, random, 2, n, n);
    hash1->create_hash_function();
    inc_memory(hash1->get_memory());

    hash2 = new Hash(prime_getter, random, 2, n, K*K*K);
    hash2->create_hash_function();
    inc_memory(hash2->get_memory());

    int k = Log10(Int(1/eps)) / Log10(Int(Log10(Int(1/eps)))) + 1;
    hash3 = new Hash(prime_getter, random, k, K*K*K, K);
    hash3->create_hash_function();
    inc_memory(hash1->get_memory());

    inc_memory(sizeof(hash1) + sizeof(hash1) + sizeof(hash1) + sizeof(rough_l0_estimator) + sizeof(K) +
        convert_to_int(K)*sizeof(Int) + sizeof(A) + sizeof(n));
}


void L0Estimator::update(Int index, Int value)
{
    rough_l0_estimator->update(index, value);

    int row = convert_to_int(
            hash3->eval_hash_function(0,
                                      hash2->eval_hash_function(0, index)));
    A[row] |= (Int(1) << lsb(hash1->eval_hash_function(0, index), n));
}

Int L0Estimator::query()
{
    Int R = rough_l0_estimator->query();
    Int T = 0;

    int log_value = Log2(Int(16*double(R)/double(K)));
    for (int j = 0; j < K; j++)
    {
        Int tmp = A[j];
        tmp <<= NUMLEN - log_value - 1;
        tmp >>= NUMLEN - 1;

        T += tmp;
    }
    if (T == K)
        T--;

    double result = 1.67*32*double(R)/double(K) * LogE(double(1) - double(T)/double(K))/LogE(double(1) - double(1)/double(K));
    return Int(result);
}

