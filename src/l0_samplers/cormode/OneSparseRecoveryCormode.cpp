//
// Created by nikita on 23.05.17.
//


#include "OneSparseRecoveryCormode.h"


OneSparseRecoveryCormode::OneSparseRecoveryCormode(Int _z, Int _p) : z(_z), p(_p)
{
    phi = tau = iota = 0;

    inc_memory(sizeof(p) + sizeof(z) + sizeof(phi) + sizeof(tau) + sizeof(iota));
}


void OneSparseRecoveryCormode::update(Int index, Int value)
{
    iota += (index + 1)*value;
    phi += value;
    tau = (tau + value * pow(z, index + 1, p)) % p;
}

pair<Int, Int> OneSparseRecoveryCormode::query()
{
    if (phi != 0 && iota % phi == 0 && iota/phi > 0 &&
        (tau = phi*pow(z, iota, p)) % p)
        return {iota/phi - 1, phi};
    return {Int(-1), Int(-1)};
}




OneSparseRecoveryCormodeInitialiser::OneSparseRecoveryCormodeInitialiser(
        Random *_random,
        PrimeGetter *_prime_getter,
        Int n,
        double one_sp_rec_err_prob,
        Int _rows,
        Int columns
) : rows(_rows)
{
    one_sp_rec_p = _prime_getter->get_next_prime(n*Int(1/one_sp_rec_err_prob));

    z_generator = new Hash(_prime_getter, _random, 2, columns*rows, one_sp_rec_p);
    z_generator->create_hash_function();
    inc_memory(z_generator->get_memory());

    inc_memory(sizeof(one_sp_rec_p) + sizeof(z_generator));
}

OneSparseRecoveryBase* OneSparseRecoveryCormodeInitialiser::init_one_sp_rec(int row, Int hash_value)
{
    return new OneSparseRecoveryCormode(
            z_generator->eval_hash_function(
                    0,
                    row*rows + hash_value
            ),
            one_sp_rec_p
    );
}