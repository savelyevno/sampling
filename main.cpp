#include <iostream>

#include "experiments/Cormode.h"

int main()
{
    test_sparse_recovery(
            int(1e6),//N
            1000,//s
            1e-3,//delta
            10000,//N
            int(1e9)//MAX
    );


    return 0;
}