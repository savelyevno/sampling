//
// Created by nikita on 21.05.17.
//

#ifndef L0SAMPLER_TESTTOOLS_H
#define L0SAMPLER_TESTTOOLS_H

#include "../pch/common.pch"
#include "../src/random/Random.h"
#include "../src/primes/PrimeGetter.h"

vector <pair <Int, Int>> get_updates(Int n, int N, int seed=1)
{
    Random* random = new Random(seed);
    set <Int> unique;

    vector<pair <Int, Int>> updates(N);
    for (int i = 0; i < N; i++)
    {
        updates[i].first = random->randint(0, n);
        while (unique.find(updates[i].first) != unique.end())
            updates[i].first = random->randint(0, n);

        updates[i].second = random->randint(1, MAXVAL + 1);

        unique.insert(updates[i].first);
    }

    return updates;
};

set<Int> get_unique(vector <pair <Int, Int> > updates)
{
    set<Int> result;
    for (int i = 0; i < updates.size(); i++)
        result.insert(updates[i].first);
    return result;
}

#endif //L0SAMPLER_TOOLS_H
