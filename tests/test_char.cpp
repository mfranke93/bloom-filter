#include <iostream>
#include <array>
#include <algorithm>

#include "../lib/bloom_filter"

int main()
{
    constexpr size_t const num_hash_fns = 8;
    constexpr size_t const precision    = 4;

    std::array<char, 20> chars =
    { -75, 112, 95, -24, 77, -43, 126, 114, -66, 117, -18, -110, -68, -51, -36, 35, -116, -56, 51, 114 };

    bloom_filter<char, num_hash_fns, precision> filter;
    for (auto& c : chars)
    {
        filter.add(c);
    }

    if (std::all_of(chars.cbegin(), chars.cend(),
                [&filter](auto const& c) { return filter.test(c); }))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
