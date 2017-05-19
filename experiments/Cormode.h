//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_CORMODE_H
#define L0SAMPLER_CORMODE_H

#include "../src/l0_samplers/cormode/L0SamplerCormode.h"
#include "../src/timer/Timer.h"

template <class SpRecClass>
void test_sparse_recovery(Int n, Int s, double delta, int N, Int MAXVAL)
{
    int seed = 1;
    Random* prime_getter_random = new Random(seed);
    PrimeGetter* prime_getter = new PrimeGetter(prime_getter_random);

    Random* sp_rec_random = new Random(seed);

    SpRecClass* sp_rec = new SpRecClass(
            sp_rec_random,
            prime_getter,
            n,
            s,
            delta,
            1e-2
    );

    Random* random = new Random(seed);
    pair <Int, Int>* updates = new pair<Int, Int>[N];
    set <Int> unique;
    for (int i = 0; i < N; i++)
    {
        updates[i].first = random->randint(0, n);
        updates[i].second = random->randint(1, MAXVAL + 1);

        unique.insert(updates[i].first);

        sp_rec->update(updates[i].first, updates[i].second);
    }

    auto result = sp_rec->query();

    cout << result.size() << " " << unique.size() << endl;
}


template <class L0SamplerClass>
void test_l0_sampler_recovery(
        Int n,
        double delta,
        double sp_rec_delta,
        double one_sp_rec_err_prob,
        int k,
        int N,
        Int MAXVAL)
{
    int seed = 1;
    Random* prime_getter_random = new Random(seed);
    PrimeGetter* prime_getter = new PrimeGetter(prime_getter_random);

    int gen_seed = 4;
    Random* random = new Random(gen_seed);
    pair <Int, Int>* updates = new pair<Int, Int>[N];
    set <Int> unique;
    for (int i = 0; i < N; i++)
    {
        updates[i].first = random->randint(0, n);
        updates[i].second = random->randint(1, MAXVAL + 1);

        unique.insert(updates[i].first);
    }

    L0SamplerClass* l0_sampler = new L0SamplerClass(
            prime_getter,
            n,
            delta,
            sp_rec_delta,
            one_sp_rec_err_prob,
            k,
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


#endif //L0SAMPLER_CORMODE_H
