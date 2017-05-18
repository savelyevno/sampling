//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_L0SAMPLERCORMODE_H
#define L0SAMPLER_L0SAMPLERCORMODE_H

#include "../base_classes/L0SamplerBase.h"
#include "../../primes/PrimeGetter.h"
#include "../../hash/Hash.h"

template <typename SpRecClass>
struct L0SamplerCormode : L0SamplerBase
{
    Int n, levels, k;
    Hash* level_hash;
    SpRecClass** sparse_recoverers;
    Hash* tmp_hash;
    vector <int> cnt_lvl;

    L0SamplerCormode(
            PrimeGetter* _prime_getter,
            Int _n,
            double delta,
            double sp_rec_delta,
            double _one_sp_rec_err_prob,
            Int _k,
            Int init_seed
    )
    {
        Random* random;
        if (init_seed == 0)
            random = new Random();
        else
            random = new Random(init_seed);

        n = _n;

        levels = Int(ceil(log2(n))) + 1;

        Int s = Int(ceil(2*log2(1/delta)));
        if (_k == -1)
            k = s/2;
        else
            k = _k;

        level_hash = new Hash(_prime_getter, random, k, n, n);
        level_hash->create_hash_function();

        sparse_recoverers = new SpRecClass*[levels];
        for (int level = 0; level < levels; level++)
            sparse_recoverers[level] = new SpRecClass(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta,
                    _one_sp_rec_err_prob
            );

        tmp_hash = new Hash(_prime_getter, random, k, n, n);
        for (int level = 0; level < levels; level++)
            tmp_hash->create_hash_function();

        cnt_lvl.resize(levels);
    }


    void update(Int index, Int value)
    {
        if (0)
        {
            Int hash = level_hash->eval_hash_function(0, index),
                    x = n, level = 0;

            while (x >= hash)
            {
                sparse_recoverers[level]->update(index, value);
                cnt_lvl[level]++;

                if (x == 0)
                    x = -1;
                else
                    x >>= 1;
                level++;
            }
        }
        else
        {
            for (int level = 0; level < levels; level++)
            {
                Int hash = tmp_hash->eval_hash_function(level, index);
                if (n >> level >= hash)
                {
                    cnt_lvl[level]++;
                    sparse_recoverers[level]->update(index, value);
                }
            }
        }
    }


    Set < pair<Int, Int> > query()
    {
        Set <pair <Int, Int> > result;

        for (int level = 0; level < levels; level++)
        {
            auto level_result = sparse_recoverers[level]->query();

            Int old_size = result.size();

            result.insert(level_result.begin(), level_result.end());

//        cout << level << " " << Int(result.size()) - old_size << endl;
        }

        return result;
    }

};


#endif //L0SAMPLER_L0SAMPLERCORMODE_H
