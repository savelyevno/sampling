//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_XORSHIFTPLUSRANDOM_H
#define L0SAMPLER_XORSHIFTPLUSRANDOM_H

#include "RandomBase.h"
#include <random>
#include <random>

struct XorShiftPlusRandom : public RandomBase
{
    uint64_t state[2];
    XorShiftPlusRandom(uint64_t init_state[2]);
    XorShiftPlusRandom(int seed);
    XorShiftPlusRandom();

    void seed(int seed);

    Int getrandbits();

    //not including b
    Int randint(Int a, Int b);
};


#endif //L0SAMPLER_XORSHIFTPLUSRANDOM_H
