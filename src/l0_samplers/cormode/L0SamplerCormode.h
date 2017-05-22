//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_L0SAMPLERCORMODE_H
#define L0SAMPLER_L0SAMPLERCORMODE_H


#include "../base_classes/L0SamplerBase.h"
#include "../../primes/PrimeGetter.h"
#include "../../hash/Hash.h"
#include "../../base_class/BaseClass.h"
#include "../base_classes/SparseRecoveryBase.h"
#include "SparseRecoveryCormode.h"
#include "../barkay/FRS.h"


struct L0SamplerCormodeBase : L0SamplerBase
{
    int k, levels, s;
    Int n;
    Hash* level_hash;
    Random* random;
    SparseRecoveryBase** sparse_recoverers;
    vector <int> cnt_lvl;

    L0SamplerCormodeBase(
            PrimeGetter* _prime_getter,
            Int _n,
            int _s,
            int _k,
            int init_seed
    ) : n(_n), s(_s)
    {
        if (init_seed == 0)
            random = new Random();
        else
            random = new Random(init_seed);

        levels = Log2(n) + 1;

//        s = int(ceil(2*log2(1/delta)));
        if (_k == -1)
            k = s/2;
        else
            k = _k;

        level_hash = new Hash(_prime_getter, random, k, n, n);
        level_hash->create_hash_function();
        inc_memory(level_hash->get_memory());

        sparse_recoverers = new SparseRecoveryBase*[levels];

        cnt_lvl.resize(size_t(levels));


        inc_memory(sizeof(n) + sizeof(levels) + sizeof(k) + sizeof(sparse_recoverers) + sizeof(level_hash) +
                sizeof(s) + sizeof(random));
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



struct L0SamplerCormode_SparseRecoveryCormode_OneSparseRecoveryCormode : L0SamplerCormodeBase
{
    L0SamplerCormode_SparseRecoveryCormode_OneSparseRecoveryCormode(PrimeGetter* _prime_getter,
                                                                    Int _n,
                                                                    int s,
                                                                    double sp_rec_delta,
                                                                    double one_sp_rec_err_prob,
                                                                    int _k,
                                                                    int init_seed):
            L0SamplerCormodeBase(_prime_getter,
                                 _n,
                                 s,
                                 _k,
                                 init_seed
            )
    {
        for (int level = 0; level < levels; level++)
        {
            sparse_recoverers[level] = new SparseRecoveryCormode_OneSparseRecoveryCormode(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta,
                    one_sp_rec_err_prob
            );
            inc_memory(sizeof(sparse_recoverers[level]));
        }
    }
};



struct L0SamplerCormode_SparseRecoveryCormode_StrictBinSketch : L0SamplerCormodeBase
{
    L0SamplerCormode_SparseRecoveryCormode_StrictBinSketch(PrimeGetter* _prime_getter,
                                                           Int _n,
                                                           int s,
                                                           double sp_rec_delta,
                                                           double one_sp_rec_err_prob,
                                                           int _k,
                                                           int init_seed):
            L0SamplerCormodeBase(_prime_getter,
                                 _n,
                                 s,
                                 _k,
                                 init_seed
            )
    {
        for (int level = 0; level < levels; level++)
        {
            sparse_recoverers[level] = new SparseRecoveryCormode_StrictBinSketch(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta
            );
            inc_memory(sizeof(sparse_recoverers[level]));
        }
    }
};



struct L0SamplerCormode_SparseRecoveryCormode_BinSketch : L0SamplerCormodeBase
{
    L0SamplerCormode_SparseRecoveryCormode_BinSketch(PrimeGetter* _prime_getter,
                                                     Int _n,
                                                     int s,
                                                     double sp_rec_delta,
                                                     double one_sp_rec_err_prob,
                                                     int _k,
                                                     int init_seed):
            L0SamplerCormodeBase(_prime_getter,
                                 _n,
                                 s,
                                 _k,
                                 init_seed
            )
    {
        for (int level = 0; level < levels; level++)
        {
            sparse_recoverers[level] = new SparseRecoveryCormode_BinSketch(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta,
                    one_sp_rec_err_prob,
                    10   //t
            );
            inc_memory(sizeof(sparse_recoverers[level]));
        }
    }
};






struct L0SamplerCormodeModifiedBase : L0SamplerCormodeBase
{
    Hash* level_hash;

    L0SamplerCormodeModifiedBase(PrimeGetter* _prime_getter,
                                 Int _n,
                                 int s,
                                 int _k,
                                 int init_seed) :
            L0SamplerCormodeBase(_prime_getter,
                                 _n,
                                 s,
                                 _k,
                                 init_seed
            )
    {
        level_hash = new Hash(_prime_getter, random, k, n, n);
        for (int level = 0; level < levels; level++)
            level_hash->create_hash_function();
        inc_memory(level_hash->get_memory());
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
};



struct L0SamplerCormodeModified_SparseRecoveryCormode_OneSparseRecoveryCormode : L0SamplerCormodeModifiedBase
{
    Hash* level_hash;

    L0SamplerCormodeModified_SparseRecoveryCormode_OneSparseRecoveryCormode(PrimeGetter* _prime_getter,
                                                                            Int _n,
                                                                            int s,
                                                                            double sp_rec_delta,
                                                                            double one_sp_rec_err_prob,
                                                                            int _k,
                                                                            int init_seed):
            L0SamplerCormodeModifiedBase(_prime_getter,
                                         _n,
                                         s,
                                         _k,
                                         init_seed
            )
    {
        for (int level = 0; level < levels; level++)
        {
            sparse_recoverers[level] = new SparseRecoveryCormode_OneSparseRecoveryCormode(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta,
                    one_sp_rec_err_prob
            );
            inc_memory(sizeof(sparse_recoverers[level]));
        }
    }
};



struct L0SamplerCormodeModified_SparseRecoveryCormode_StrictBinSketch : L0SamplerCormodeModifiedBase
{
    Hash* level_hash;

    L0SamplerCormodeModified_SparseRecoveryCormode_StrictBinSketch(PrimeGetter* _prime_getter,
                                                                   Int _n,
                                                                   int s,
                                                                   double sp_rec_delta,
                                                                   double one_sp_rec_err_prob,
                                                                   int _k,
                                                                   int init_seed):
            L0SamplerCormodeModifiedBase(_prime_getter,
                                         _n,
                                         s,
                                         _k,
                                         init_seed
            )
    {
        for (int level = 0; level < levels; level++)
        {
            sparse_recoverers[level] = new SparseRecoveryCormode_StrictBinSketch(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta
            );
            inc_memory(sizeof(sparse_recoverers[level]));
        }
    }
};



struct L0SamplerCormodeModified_SparseRecoveryCormode_BinSketch : L0SamplerCormodeModifiedBase
{
    Hash* level_hash;

    L0SamplerCormodeModified_SparseRecoveryCormode_BinSketch(PrimeGetter* _prime_getter,
                                                             Int _n,
                                                             int s,
                                                             double sp_rec_delta,
                                                             double one_sp_rec_err_prob,
                                                             int _k,
                                                             int init_seed):
            L0SamplerCormodeModifiedBase(_prime_getter,
                                         _n,
                                         s,
                                         _k,
                                         init_seed
            )
    {
        for (int level = 0; level < levels; level++)
        {
            sparse_recoverers[level] = new SparseRecoveryCormode_BinSketch(
                    random,
                    _prime_getter,
                    n,
                    s,
                    sp_rec_delta,
                    one_sp_rec_err_prob,
                    10   //t
            );
            inc_memory(sizeof(sparse_recoverers[level]));
        }
    }
};






#endif //L0SAMPLER_L0SAMPLERCORMODE_H
