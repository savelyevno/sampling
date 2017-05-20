//
// Created by nikita on 16.05.17.
//

#ifndef L0SAMPLER_REGULARHASH_H
#define L0SAMPLER_REGULARHASH_H

#include "HashBase.h"


struct RegularHash : HashBase
{
    RegularHash(PrimeGetter* prime_getter, Random* _random, int _degree, Int _domain_size, Int _image_size);

    int create_hash_function();

    int create_hash_function(Random* _random);

    Int eval_hash_function(int id, Int arg);

    Int* eval_hash_function_at_several_points(int id, Int* arg);
};


#endif //L0SAMPLER_REGULARHASH_H
