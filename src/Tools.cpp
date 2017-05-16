//
// Created by nikita on 15.05.17.
//

#include "Tools.h"

Int pow(ll a, ll b, ll p)
{
    assert(p < (1LL << 32));

    ll result = 1;
    while (b > 0)
    {
        if (b & 1)
            result = (result * a) % p;

        a = (a*a) % p;
        b >>= 1;
    }

    return Int(result);
}