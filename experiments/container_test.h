//
// Created by nikita on 19.05.17.
//

#ifndef L0SAMPLER_CONTAINER_TEST_H
#define L0SAMPLER_CONTAINER_TEST_H

#include "../pch/common.pch"

void test_container()
{
#ifdef BOOST
    boost::unordered_map <pair<Int, Int>, int> a;
    a[{Int(1) << 100, Int(1) << 100}] = 2;
    a[{Int(1) << 100, Int(1) << 101}] = 2;
    a[{Int(1) << 100, Int(1) << 102}] = 2;

    for (auto it: a)
        cout << it.first.first << " " << it.first.second << " " << it.second << endl;
    cout << endl;

    auto hf = a.hash_function();

    for (auto it: a)
        cout << "hash(" << it.first.first << ", " << it.first.second << ") = " << hf(it.first) << endl;
    cout << endl;

    unsigned nbuckets = a.bucket_count();

    std::cout << "mymap has " << nbuckets << " buckets:\n";

    for (unsigned i=0; i<nbuckets; ++i) {
        std::cout << "bucket #" << i << " has " << a.bucket_size(i) << " elements.\n";
    }

    cout << a.bucket_count();
#endif
}

#endif //L0SAMPLER_CONTAINER_TEST_H
