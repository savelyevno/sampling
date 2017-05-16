#include <iostream>

#include "src/l0_samplers/cormode/settings.h"
#include "src/random/Random.h"
#include "src/primes/PrimeGetter.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    uint64_t  init_state[2] = {1, 1};
    Random* random = new Random(init_state);

    uint64_t  prime_getter_init_state[2] = {1, 1};
    Random* prime_getter_random = new Random(prime_getter_init_state);
    PrimeGetter* prime_getter = new PrimeGetter(prime_getter_random);

    SparseRecoveryBase* asd = new SparseRecovery(random, prime_getter, 1000, 10, 1e-2, 1e-2);
//    asd->update(0, 1);
//    asd->update(1, 1);
//    asd->update(2, 1);
//    asd->update(3, 1);
//    asd->update(4, 1);
//
//    auto rec = asd->query();
//
//    for (auto it: rec)
//        cout << it.first << " " << it.second << endl;

    return 0;
}