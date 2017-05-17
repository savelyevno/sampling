#include <iostream>

#include "experiments/Cormode.h"
#include "src/timer/Timer.h"

int main()
{
    start_timer();

//    test_sparse_recovery(
//            int(1e6),//N
//            1000,//s
//            1e-3,//delta
//            10000,//N
//            int(1e9)//MAX
//    );

    test_l0_sampler_recovery(
            int(1e7), //n
            1e-2,//delta
            1e-2,//sparse recovery delta
            1e-2,//one sparse recovery error probability
            -1,//k
            int(1e5),//N
            int(1e9)//MAX
    );

    stop_timer("Running time: ");

    return 0;
}