#include <iostream>

#include "experiments/Cormode.h"
#include "experiments/container_test.h"
#include "src/l0_samplers/cormode/SparseRecoveryCormode.h"
#include "src/l0_samplers/cormode/OneSparseRecoveryCormode.h"
#include "src/l0_samplers/barkay/StrictBinSketch.h"
#include "experiments/l0_estimator_test.h"

int main()
{
    start_timer();

    Int n = Int(1) << 30;
    ll N = ll(1e2);
    int seed = 13245;

//    test_sparse_recovery<SparseRecoveryCormode<OneSparseRecoveryCormode>>(
//            Int(1e6),//N
//            1000,//s
//            1e-3,//delta
//            10000//N
//    );


//    test_l0_sampler_recovery<L0SamplerCormodeModified<SparseRecoveryCormode_StrictBinSketch>>(
//            Int(1) << 20,//n
//            1e-2,//delta
//            1e-2,//sparse recovery delta
//            1e-2,//one sparse recovery error probability
//            -1,//k
//            ll(1e5)//N
//    );



//    test_l0_estimator(
//            n,
//            N,
//            1e-1,//eps
//            seed
//    );
//
//    cout << "_________________________________________" << endl;
//
//    test_rough_l0_estimator(
//            n,
//            N,
//            seed
//    );

    test_multiple_l0_estimations(
            n,
            N,
            1e-2,
            1000,
            seed
    );

    //    test_container();

    stop_timer("Running time: ");

    return 0;
}