//
// Created by nikita on 15.05.17.
//

#include "XorShiftPlusRandom.h"

XorShiftPlusRandom::XorShiftPlusRandom(uint64_t init_state[2])
{
    if (init_state[0] == init_state[1] && init_state[0] == 0)
    {
        random_device rd;
        state[0] = rd();
        state[1] = rd();
    }
    else
    {
        state[0] = init_state[0];
        state[1] = init_state[1];
    }
}

void XorShiftPlusRandom::seed(Int _seed)
{
    state[0] = state[1] = uint64_t(_seed);
}

Int XorShiftPlusRandom::getrandbits()
{
    uint64_t x = state[0];
    uint64_t const y = state[1];
    state[0] = y;
    x ^= x << 23; // a
    state[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return Int(state[1] + y);
}

Int XorShiftPlusRandom::randint(Int a, Int b)
{
    return a + (uInt(getrandbits()) % b);
}

XorShiftPlusRandom::XorShiftPlusRandom(Int _seed)
{
    seed(_seed);
}

XorShiftPlusRandom::XorShiftPlusRandom()
{
    random_device rd;
    state[0] = state[1] = uint64_t(rd());
}
