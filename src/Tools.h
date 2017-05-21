//
// Created by nikita on 15.05.17.
//

#ifndef L0SAMPLER_TOOLS_H
#define L0SAMPLER_TOOLS_H

#include "../pch/common.pch"

Int pow(Int a, Int b, Int p);

int Log2(Int x);

int Log10(Int x);

double LogE(double x);

#ifdef BOOST

size_t get_first_half(boost::multiprecision::int128_t x);

size_t get_second_half(boost::multiprecision::int128_t x);

#endif

int lsb(Int x, Int n);

int convert_to_int(Int x);

#endif //L0SAMPLER_TOOLS_H
