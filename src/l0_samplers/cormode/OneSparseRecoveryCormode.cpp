//
// Created by nikita on 15.05.17.
//

#include "OneSparseRecoveryCormode.h"

OneSparseRecoveryCormode::OneSparseRecoveryCormode(Random *_random,
                                                   PrimeGetter *_prime_getter,
                                                   Int _n,
                                                   double failure_probability)
{
    random = _random;
    prime_getter = _prime_getter;

    p = prime_getter->get_next_prime(Int(_n/failure_probability));
    z = random->randint(1, p);

    phi = tau = iota = 0;
}

void OneSparseRecoveryCormode::update(Int index, Int value)
{
    iota += (index + 1)*value;
    phi += value;
    tau = (tau + value * pow(z, index + 1, p)) % p;
}

pair <Int, Int> OneSparseRecoveryCormode::query()
{
    if (phi != 0 && iota % phi == 0 && iota/phi > 0 &&
            (tau = phi*pow(z, iota, p)) % p)
        return {iota/phi - 1, phi};
    return {-1, -1};
}
