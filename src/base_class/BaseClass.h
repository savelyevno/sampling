//
// Created by nikita on 18.05.17.
//

#ifndef L0SAMPLER_BASECLASS_H
#define L0SAMPLER_BASECLASS_H


struct BaseClass
{
    long long memory_used;

    BaseClass();

    void inc_memory(long long amount);

    void dec_memory(long long amount);

    virtual long long get_memory();
};


#endif //L0SAMPLER_BASECLASS_H
