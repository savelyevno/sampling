//
// Created by nikita on 16.05.17.
//

#include "RegularHash.h"

RegularHash::RegularHash(PrimeGetter* prime_getter, Random* _random, int degree, Int _domain_size, Int _image_size) :
        HashBase(prime_getter, _random, degree, _domain_size, _image_size)
{

}

Int RegularHash::create_hash_function()
{
    Int* new_coefficients = new Int[degree];
    for (int i = 0; i < degree; i++)
        if (i == degree - 1)
            new_coefficients[i] = random->randint(1, field_order);
        else
            new_coefficients[i] = random->randint(0, field_order);

    coefficients.push_back(new_coefficients);
    return Int(coefficients.size()) - 1;
}

Int RegularHash::eval_hash_function(Int id, Int arg)
{
    Int result = 0;


    for (Int i = degree - 1; i >= 0; i--)
        result = ((result * arg + coefficients[id][i]) % field_order);

    return result % image_size;
}

Int *RegularHash::eval_hash_function_at_several_points(Int id, Int *arg)
{
    return nullptr;
}
