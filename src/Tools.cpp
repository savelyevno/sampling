//
// Created by nikita on 15.05.17.
//

#include "Tools.h"

Int pow(Int a, Int b, Int p)
{
    #ifndef BOOST
        assert(p < (1LL << 32));
    #endif

    Int result = 1;
    while (b > 0)
    {
        if (b & 1)
            result = (result * a) % p;

        a = (a*a) % p;
        b >>= 1;
    }

    return result;
}

int Log2(Int x)
{
    int result = 0;

    while (x > 0)
    {
        x /= 2;
        result++;
    }

    return result;
}


#ifdef BOOST

size_t get_first_half(boost::multiprecision::int128_t x)
{
    return (x >> 64).convert_to<size_t>();
}

size_t get_second_half(boost::multiprecision::int128_t x)
{
    return ((x << 64) >> 64).convert_to<size_t>();
}

#endif