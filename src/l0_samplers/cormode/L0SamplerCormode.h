//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_L0SAMPLERCORMODE_H
#define L0SAMPLER_L0SAMPLERCORMODE_H

#include "../base_classes/L0SamplerBase.h"
#include "../../primes/PrimeGetter.h"
#include "../../hash/Hash.h"
#include "../../base_class/BaseClass.h"


template <typename SpRecClass>
struct L0SamplerCormode : L0SamplerBase
{
    int k;
    Int n, levels;
    Hash* level_hash;
    SpRecClass** sparse_recoverers;
    vector <int> cnt_lvl;

    L0SamplerCormode(
            PrimeGetter* _prime_getter,
            Int _n,
            double delta,
            double sp_rec_delta,
            double _one_sp_rec_err_prob,
            int _k,
            Int init_seed
    ) : BaseClass()
    {
        inc_memory(sizeof(n) + sizeof(levels) + sizeof(k));

        Random* random;
        if (init_seed == 0)
            random = new Random();
        else
            random = new Random(init_seed);

        n = _n;

        levels = Log2(n) + 1;

        int s = int(ceil(2*log2(1/delta)));
        if (_k == -1)
            k = s/2;
        else
            k = _k;

        level_hash = new Hash(_prime_getter, random, k, n, n);
        level_hash->create_hash_function();
        inc_memory(level_hash->get_memory());

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

        cnt_lvl.resize(size_t(levels));
    }


    void update(Int index, Int value)
    {
        Int hash = level_hash->eval_hash_function(0, index),
                x = n;
        int level = 0;

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


    Set < pair<Int, Int> > query()
    {
        Set <pair <Int, Int> > result;

        for (int level = 0; level < levels; level++)
        {
            auto level_result = sparse_recoverers[level]->query();

            Int old_size = Int(result.size());

            result.insert(level_result.begin(), level_result.end());
        }

        return result;
    }


    ll get_memory()
    {
        ll result = memory_used;
        for (int level = 0; level < levels; level++)
        {
            result += sparse_recoverers[level]->get_memory();
        }
        return result;
    }
};


template <typename SpRecClass>
struct L0SamplerCormodeModified : L0SamplerBase
{
    Int n;
    int k, levels;
    SpRecClass** sparse_recoverers;
    Hash* level_hash;
    vector <int> cnt_lvl;

    L0SamplerCormodeModified(
            PrimeGetter* _prime_getter,
            Int _n,
            double delta,
            double sp_rec_delta,
            double _one_sp_rec_err_prob,
            int _k,
            int init_seed
    )
    {
        inc_memory(sizeof(n) + sizeof(levels) + sizeof(k));

        Random* random;
        if (init_seed == 0)
            random = new Random();
        else
            random = new Random(init_seed);

        n = _n;

        levels = Log2(n) + 1;

        int s = int(ceil(2*log2(1/delta)));
        if (_k == -1)
            k = s/2;
        else
            k = _k;


        level_hash = new Hash(_prime_getter, random, k, n, n);
        for (int level = 0; level < levels; level++)
            level_hash->create_hash_function();
        inc_memory(level_hash->get_memory());


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

        cnt_lvl.resize(size_t(levels));
    }


    void update(Int index, Int value)
    {
        for (int level = 0; level < levels; level++)
        {
            Int hash = level_hash->eval_hash_function(level, index);
            if (n >> level >= hash)
            {
                cnt_lvl[level]++;
                sparse_recoverers[level]->update(index, value);
            }
        }

    }


    Set < pair<Int, Int> > query()
    {
        Set <pair <Int, Int> > result;

        for (int level = 0; level < levels; level++)
        {
            auto level_result = sparse_recoverers[level]->query();

            Int old_size = Int(result.size());

            result.insert(level_result.begin(), level_result.end());
        }

        return result;
    }


    ll get_memory()
    {
        ll result = memory_used;
        for (int level = 0; level < levels; level++)
        {
            result += sparse_recoverers[level]->get_memory();
        }
        return result;
    }
};




#endif //L0SAMPLER_L0SAMPLERCORMODE_H
