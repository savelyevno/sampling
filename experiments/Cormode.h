//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_CORMODE_H
#define L0SAMPLER_CORMODE_H

#include "../src/l0_samplers/cormode/L0SamplerCormode.h"

void test_sparse_recovery(Int n, Int s, double delta, int N, int MAXVAL)
{
    Int seed = 1;
    Random* prime_getter_random = new Random(seed);
    PrimeGetter* prime_getter = new PrimeGetter(prime_getter_random);

    Random* sp_rec_random = new Random(seed);

    SparseRecovery* sp_rec = new SparseRecovery(
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


#endif //L0SAMPLER_CORMODE_H
