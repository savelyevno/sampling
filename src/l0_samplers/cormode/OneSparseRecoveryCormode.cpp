//
// Created by nikita on 15.05.17.
//

#include "OneSparseRecoveryCormode.h"

OneSparseRecoveryCormode::OneSparseRecoveryCormode(Int _p,
                                                   Int _z)
{
    p = _p;
    z = _z;

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
