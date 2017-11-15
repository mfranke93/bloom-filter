#include <set>
#include <random>
#include <iostream>
#include <string>

#include "../lib/bloom_filter"

int main()
{
    constexpr size_t const num_hash_fns = 12;
    constexpr size_t const precision    = 12;

    constexpr size_t const num_test_items { 100000 };
    std::default_random_engine generator;
    std::uniform_int_distribution<int> dist (
            std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::set<int> integers;
    bloom_filter<int, num_hash_fns, precision> filter;
    for (size_t i = 0; i < num_test_items; ++i) 
    {
        auto const x = dist(generator);
        integers.insert(x);
        filter.add(x);
    }

    // check true positives
    for (auto& i : integers)
    {
        if (not filter.test(i))
        {
            std::cerr << "Tested for membership of value and got false negative!\n";
            return 1;
        }
    }
}
