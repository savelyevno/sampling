//
// Created by nikita on 16.05.17.
//

#ifndef L0SAMPLER_HASHBASE_H
#define L0SAMPLER_HASHBASE_H


#include "../../pch/common.pch"
#include "../primes/PrimeGetter.h"
#include "../random/Random.h"

struct HashBase
{
    Int hash_function_counter, degree, domain_size, image_size, field_order;
    Vector <Int*> coefficients;
    Random* random;


    HashBase(PrimeGetter* prime_getter, Random* _random, int degree, Int _domain_size, Int _image_size);

    virtual Int create_hash_function()=0;

    virtual Int eval_hash_function(Int id, Int arg)=0;

    virtual Int* eval_hash_function_at_several_points(Int id, Int* arg)=0;
};



#endif //L0SAMPLER_HASHBASE_H
