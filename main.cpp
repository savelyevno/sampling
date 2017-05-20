#include <iostream>

#include "experiments/Cormode.h"
#include "experiments/container_test.h"
#include "src/l0_samplers/cormode/SparseRecoveryCormode.h"
#include "src/l0_samplers/cormode/OneSparseRecoveryCormode.h"
#include "src/l0_samplers/barkay/StrictBinSketch.h"


int main()
{
    start_timer();

//    test_sparse_recovery<SparseRecoveryCormode<OneSparseRecoveryCormode>>(
//            Int(1e6),//N
//            1000,//s
//            1e-3,//delta
//            10000,//N
//            Int(1e9)//MAX
//    );


    test_l0_sampler_recovery<L0SamplerCormodeModified<SparseRecoveryCormode_StrictBinSketch>>(
            Int(1) << 20,//n
            1e-2,//delta
            1e-2,//sparse recovery delta
            1e-2,//one sparse recovery error probability
            -1,//k
            ll(1e5),//N
            ll(1e3)//MAX
    );


    stop_timer("Running time: ");

//    test_container();

    return 0;
}