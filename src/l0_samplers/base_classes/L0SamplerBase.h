//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_L0SAMPLERBASE_H
#define L0SAMPLER_L0SAMPLERBASE_H

#include "../../../pch/common.pch"

class L0SamplerBase
{
    void update(Int index, Int value);

    pair<Int, Int> query();
};


#endif //L0SAMPLER_L0SAMPLERBASE_H
