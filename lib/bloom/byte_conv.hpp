#include <cstring>
#include <cstdint>
#include <array>
#include <algorithm>

#pragma once

namespace detail {
    template<typename T>
    struct byte_conv
    {
        constexpr static size_t const size = sizeof(T);
        using bytearray_t = std::array<uint8_t, size>;


        byte_conv() = default;
        ~byte_conv() = default;

        constexpr bytearray_t operator()(T t) const
        {
            auto arr = std::array<uint8_t, size>();
            std::memcpy(arr.data(), &t, size);
            return arr;
        }
    };

    template<typename Iter>
    constexpr size_t
    compress_byte_array(Iter begin, Iter end)
    {
        size_t const bytes_per_round = sizeof(size_t);
        size_t idx {0};
        size_t ret_val {0};
        std::for_each(begin, end,
                [&](uint8_t x)
                {
                    size_t s = x;
                    s <<= idx * 8;
                    ret_val = ret_val xor s;
                    ++idx;
                    idx %= bytes_per_round;
                }
            );
        return ret_val;
    }

    template<typename T>
    constexpr size_t
    reduce_object(T t)
    {
        byte_conv<T> b;
        auto byte_arr = b(t);
        return compress_byte_array(std::begin(byte_arr), std::end(byte_arr));
    }
} // namespace detail

