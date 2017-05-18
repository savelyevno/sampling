//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_ONESPARSERECOVERYCORMODE_H
#define L0SAMPLER_ONESPARSERECOVERYCORMODE_H

#include "../../../pch/common.pch"
#include "../base_classes/OneSparseRecoveryBase.h"
#include "../../random/Random.h"
#include "../../primes/PrimeGetter.h"

struct OneSparseRecoveryCormode : OneSparseRecoveryBase
{
    Int p, z, iota, phi, tau;

    OneSparseRecoveryCormode(Int _p,
                             Int _z)
    {
        p = _p;
        z = _z;

        phi = tau = iota = 0;
    }

    void update(Int index, Int value)
    {
        iota += (index + 1)*value;
        phi += value;
        tau = (tau + value * pow(z, index + 1, p)) % p;
    }

    pair<Int, Int> query()
    {
        if (phi != 0 && iota % phi == 0 && iota/phi > 0 &&
            (tau = phi*pow(z, iota, p)) % p)
            return {iota/phi - 1, phi};
        return {-1, -1};
    }

};


#endif //L0SAMPLER_ONESPARSERECOVERYCORMODE_H
