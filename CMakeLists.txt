cmake_minimum_required(VERSION 3.7)
project(L0Sampler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/l0_samplers/base_classes/OneSparseRecoveryBase.h src/l0_samplers/base_classes/SparseRecoveryBase.h pch/common.pch src/l0_samplers/cormode/OneSparseRecoveryCormode.cpp src/l0_samplers/cormode/OneSparseRecoveryCormode.h src/l0_samplers/base_classes/L0SamplerBase.h src/random/RandomBase.h src/random/XorShiftPlusRandom.cpp src/random/XorShiftPlusRandom.h src/random/Random.h src/Tools.cpp src/Tools.h src/primes/PrimeGetter.cpp src/primes/PrimeGetter.h src/l0_samplers/cormode/SparseRecoveryCormode.cpp src/l0_samplers/cormode/SparseRecoveryCormode.h src/hash/HashBase.h src/hash/RegularHash.cpp src/hash/RegularHash.h src/hash/HashBase.cpp src/hash/Hash.h src/l0_samplers/cormode/settings.h src/l0_samplers/cormode/L0SamplerCormode.cpp src/l0_samplers/cormode/L0SamplerCormode.h experiments/Cormode.h src/timer/Timer.cpp src/timer/Timer.h)
add_executable(L0Sampler ${SOURCE_FILES})