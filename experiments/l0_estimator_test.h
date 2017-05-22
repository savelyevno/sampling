//
// Created by nikita on 21.05.17.
//

#ifndef L0SAMPLER_L0_ESTIMATOR_TEST_H
#define L0SAMPLER_L0_ESTIMATOR_TEST_H

#include "Tools.h"
#include "../src/l0_estimator/L0Estimator.h"
#include "../src/timer/Timer.h"

int test_l0_estimator(Int n,
                       int N,
                       int seed=1,
                      bool report=true)
{
    int gen_seed = 1;
    auto updates = get_updates(n, N, gen_seed);
    auto unique = get_unique(updates);

    Random* prime_getter_random = new Random(seed);
    PrimeGetter* prime_getter = new PrimeGetter(prime_getter_random);

    Random* random = new Random(seed);

    L0Estimator* l0_estimator = new L0Estimator(prime_getter, random, n);

    if (report)
        cout << "L0 estimator size: " << l0_estimator->get_memory()/1e6 << "MB" << endl;

    if (report)
        start_timer();
    for (int i = 0; i < N/2; i++)
        l0_estimator->update(updates[i].first, updates[i].second);
    for (int i = 0; i < N/2; i++)
        l0_estimator->update(updates[i].first, -updates[i].second);
    for (int i = N/2; i < N; i++)
        l0_estimator->update(updates[i].first, updates[i].second);
    if (report)
    {
        stop_timer("Update time: ");
        cout << "Correct size = " << unique.size() << endl;
    }

    if (report)
        start_timer();
    int result = convert_to_int(l0_estimator->query());
    if (report)
    {
        cout << "Approximate size = " << result << endl;
        stop_timer("Query time: ");
    }

    return result;
}


void test_rough_l0_estimator(Int n,
                             int N,
                             int seed=1)
{
    int gen_seed = 1;
    auto updates = get_updates(n, N, gen_seed);
    auto unique = get_unique(updates);

    Random* prime_getter_random = new Random(seed);
    PrimeGetter* prime_getter = new PrimeGetter(prime_getter_random);

    Random* random = new Random(seed);

    RoughL0Estimator* l0_estimator = new RoughL0Estimator(random, prime_getter, n);

    cout << "L0 estimator size: " << l0_estimator->get_memory()/1e6 << "MB" << endl;

    start_timer();
    for (int i = 0; i < N; i++)
        l0_estimator->update(updates[i].first, updates[i].second);
    stop_timer("Update time: ");

    cout << "Correct size = " << unique.size() << endl;

    start_timer();
    cout << "Approximate size = " << l0_estimator->query() << endl;
    stop_timer("Query time: ");
}


void test_multiple_l0_estimations(Int n,
                                  int N,
                                  int rep,
                                  int seed=1)
{
    Random* random = new Random(seed);

    vector <int> results;
    for (int i = 0; i < rep; i++)
    {
        int trial_seed = convert_to_int(random->randint(Int(1), Int(100500)));
        results.push_back(test_l0_estimator(n, N, trial_seed, false));
    }
    sort(results.begin(), results.end());

    cout << "Median: " << results[rep/2] << endl;
}


#endif //L0SAMPLER_L0_ESTIMATOR_TEST_H
