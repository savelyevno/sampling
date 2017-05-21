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
        x >>= 1;
        result++;
    }

    return result;
}

int Log10(Int x)
{
    int result = 0;

    while (x > 0)
    {
        x /= 10;
        result++;
    }

    return result;
}

double LogE(double x)
{
    #ifdef BOOST
        return boost::math::log1p(x - 1);
    #else
        return log(x);
    #endif
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

int lsb(Int x, Int n)
{
    if (x == 0)
        return Log2(n) + 1;

    int result = 0;

    while (x % 2 == 0)
    {
        x >>= 1;
        result++;
    }

    return result;
}

int convert_to_int(Int x)
{
    #ifdef BOOST
        return x.convert_to<int>();
    #else
        return x;
    #endif
}