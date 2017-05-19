//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_TOOLS_H
#define L0SAMPLER_TOOLS_H

#include "../pch/common.pch"

Int pow(Int a, Int b, Int p);

int Log2(Int x);

#ifdef BOOST

size_t get_first_half(boost::multiprecision::int128_t x);

size_t get_second_half(boost::multiprecision::int128_t x);

#endif

#endif //L0SAMPLER_TOOLS_H
