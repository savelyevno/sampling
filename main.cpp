#include <iostream>

#include "experiments/Cormode.h"
#include "experiments/container_test.h"
#include "src/l0_samplers/cormode/SparseRecoveryCormode.h"
#include "src/l0_samplers/cormode/OneSparseRecoveryCormode.h"
#include "src/l0_samplers/barkay/StrictBinSketch.h"
#include "experiments/l0_estimator_test.h"
#include "src/l0_samplers/barkay/FRS.h"


int main()
{
    start_timer();

    Int n = Int(1) << 30;
    ll N = ll(2e4);
    int seed = 1;

//    test_multiple_l0_estimations(
//            n,
//            N,
//            10,
//            seed
//    );

//    test_sparse_recovery<SparseRecoveryCormode<OneSparseRecoveryCormode>>(
//            Int(1e6),//N
//            1000,//s
//            1e-3,//delta
//            10000//N
//    );


    test_l0_sampler_recovery<L0SamplerCormodeModified_SparseRecoveryCormode_StrictBinSketch>(
            n,//n
            1000,//s
            1e-2,//sparse recovery delta
            1e-2,//one sparse recovery error probability
            4,//k
            N//N
    );



//    test_l0_estimator(
//            n,
//            N,
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


    //    test_container();

    stop_timer("Running time: ");

    return 0;
}