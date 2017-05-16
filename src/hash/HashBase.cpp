//
// Created by nikita on 16.05.17.
//

#include "HashBase.h"


HashBase::HashBase(PrimeGetter* prime_getter, Random* _random, int _degree, Int _domain_size, Int _image_size)
{
    domain_size = _domain_size;
    image_size = _image_size;
    hash_function_counter = 0;
    degree = _degree;
    random = _random;

    field_order = prime_getter->get_next_prime(domain_size + 1);
}