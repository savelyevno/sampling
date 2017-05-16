//
// Created by nikita on 15.05.17.
//

#include "PrimeGetter.h"

PrimeGetter::PrimeGetter(Random *_random)
{
    random = _random;
}

bool PrimeGetter::is_prime(Int n)
{
    if (n == 2 || n == 3)
        return true;
    if (n == 1 ||
            n % 2 == 0 || n % 3 == 0 ||
            n % 5 == 0 || n % 7 == 0)
        return false;

    Int d = n - 1, r = 0;
    while (d % 2 == 0)
    {
        r += 1;
        d >>= 1;
    }

    for (int i = 0; i < r; i++)
    {
        Int a = random->randint(2, n);

        Int x = pow(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        bool stop = false;
        Int j = 0;
        while (j < r - 1 && !stop)
        {
            x = pow(x, 2, n);

            if (x == 1)
                return false;
            if (x == n - 1)
                stop = true;

            j += 1;
        }

        if (!stop)
            return false;
    }

    return true;
}

Int PrimeGetter::get_next_prime(Int n)
{
    if (cache.count(n) > 0)
        return cache[n];

    Int p = n;
    if (p & 0)
        p++;

    while (!is_prime(p))
        p += 2;

    cache[n] = p;

    return p;
}
