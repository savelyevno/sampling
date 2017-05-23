//
// Created by nikita on 23.05.17.
//

#ifndef L0SAMPLER_FRSTEST_H
#define L0SAMPLER_FRSTEST_H


#include "../pch/common.pch"
#include "../src/random/Random.h"
#include "../src/primes/PrimeGetter.h"
#include "Tools.h"
#include "../src/timer/Timer.h"


template <class FRSClass>
void test_FRS_recovery(
        Int n,
        double delta,
        int K,
        int N)
{
    int seed = 1;
    Random* prime_getter_random = new Random(seed);
    PrimeGetter* prime_getter = new PrimeGetter(prime_getter_random);

    auto updates = get_updates(n, N, seed);
    auto unique = get_unique(updates);

    FRSClass* l0_sampler = new FRSClass(
            prime_getter,
            n,
            K,
            delta,
            seed
    );

    cout << "Memory: " << l0_sampler->get_memory()/1e6 << " MB" << endl;

    start_timer();
    for (int i = 0; i < N; i++)
        l0_sampler->update(updates[i].first, updates[i].second);
    stop_timer("L0 sampler update time: ");

    cout << "Memory: " << l0_sampler->get_memory()/1e6 << " MB" << endl;

    start_timer();
    auto result = l0_sampler->query();
    stop_timer("L0 sampler query time: ");


    cout << "recovered " << result.size() << " out of " << unique.size() << endl;

//    for (int i = 0; i < l0_sampler->levels; i++)
//        cout << i << ": " << l0_sampler->cnt_lvl[i] << endl;

}

#endif //L0SAMPLER_FRS_H
