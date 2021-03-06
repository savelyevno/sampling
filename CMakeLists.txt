cmake_minimum_required(VERSION 3.7)
project(L0Sampler)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58.0 COMPONENTS system filesystem REQUIRED system serialization)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp src/l0_samplers/base_classes/OneSparseRecoveryBase.h src/l0_samplers/base_classes/SparseRecoveryBase.h pch/common.pch src/l0_samplers/cormode/OneSparseRecoveryCormode.h src/l0_samplers/base_classes/L0SamplerBase.h src/random/RandomBase.h src/random/XorShiftPlusRandom.cpp src/random/XorShiftPlusRandom.h src/random/Random.h src/Tools.cpp src/Tools.h src/primes/PrimeGetter.cpp src/primes/PrimeGetter.h src/l0_samplers/cormode/SparseRecoveryCormode.h src/hash/HashBase.h src/hash/RegularHash.cpp src/hash/RegularHash.h src/hash/HashBase.cpp src/hash/Hash.h src/l0_samplers/cormode/L0SamplerCormode.h experiments/Cormode.h src/timer/Timer.cpp src/timer/Timer.h src/base_class/BaseClass.cpp src/base_class/BaseClass.h src/l0_samplers/barkay/StrictBinSketch.h src/l0_samplers/barkay/BinSketch.h src/l0_estimator/RoughL0Estimator.cpp src/l0_estimator/RoughL0Estimator.h src/l0_estimator/L0Estimator.cpp src/l0_estimator/L0Estimator.h experiments/l0_estimator_test.h experiments/Tools.h src/l0_samplers/barkay/FRS.h src/l0_samplers/barkay/FRSLevel.h experiments/FRS.h src/l0_samplers/barkay/BinSketch.cpp src/l0_samplers/barkay/FRS.cpp src/l0_samplers/barkay/FRSLevel.cpp src/l0_samplers/barkay/StrictBinSketch.cpp src/l0_samplers/cormode/L0SamplerCormode.cpp src/l0_samplers/cormode/L0SamplerCormodeModified.cpp src/l0_samplers/cormode/L0SamplerCormodeModified.h src/l0_samplers/cormode/OneSparseRecoveryCormode.cpp src/l0_samplers/cormode/SparseRecoveryCormode.cpp)
add_executable(L0Sampler ${SOURCE_FILES})

target_link_libraries(L0Sampler ${Boost_LIBRARIES})