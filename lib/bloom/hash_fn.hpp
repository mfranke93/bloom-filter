#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <cstring>
#include <functional>
#include <limits>
#include <random>
#include <type_traits>

#pragma once

namespace detail
{
    /**
     * Represents a hash function. The function has a certain salt value and
     * represents a function
     *      f: A -> B
     * where A is the data type (size_t) and B is the result type (uint8_t).
     */
    template<size_t hash_precision>
    struct hash_fn
    {
            using data_t = size_t;
            using salt_t = size_t;
            using result_t = std::bitset<hash_precision>;

            /**
             * Conversion struct to salt data values before hashing.
             */
            struct hashable
            {
                data_t  dt;
                salt_t  st;

                /**
                 * Combine a data value and a salt value (by XOR).
                 *
                 * \return data XOR salt
                 */
                size_t combined()
                {
                    return static_cast<size_t>(dt) ^ static_cast<size_t>(st);
                }
            };

        private:
            /**
             * Salt value to be applied before hashing, to enable the use of
             * multiple hash functions with different effect. This property is
             * essential for a decently working bloom filter.
             */
            salt_t m_salt;

            /**
             * std::hash used for hashing.
             */
            std::hash<size_t> m_hash_fn;

        public:
            /*
             * Assert that the data types are uint.
             */
            static_assert(std::is_integral<data_t>::value
                    && std::is_unsigned<data_t>::value, 
                    "data type must be unsigned integer.");

            /*
             * Assert that the result type has less or equal to the amount of
             * digits of std::hash. This is essential as we could not guarantee
             * equal distribution of hash values otherwise. It should always be
             * given as result_t is of type uint8_t.
             */
            static_assert(hash_precision <= std::numeric_limits<size_t>::digits,
                    "Result type must have less or equal amount of bits as std::hash.");

            /**
             * Hash a data value.
             *
             * \param _p1   Data value
             * \return      Hash value
             */
            result_t operator()(data_t const& data) const
            {
                hashable h {data, m_salt};
                auto hash = m_hash_fn(h.combined());

                // properly reduce the size_t to a uint8_t
                result_t result;
                result.reset();
                std::bitset<8*sizeof(hash)> intermediate (hash);
                for (size_t i = 0; i < intermediate.size(); ++i)
                {
                    size_t const idx = i % result.size();
                    if (intermediate.test(i)) result.flip(idx);
                }

                return result;
            }

            /**
             * Constructor.
             *
             * \param salt_value    Salt value to be used for hashing
             */
            hash_fn(salt_t const salt_value)
            :   m_salt(salt_value)
            {
                // ctor
            }

            /**
             * Move constructor.
             *
             * \param other     Other hash_fn object (moved from)
             */
            hash_fn(hash_fn&& other)
            :   m_salt(other.m_salt),
                m_hash_fn(other.m_hash_fn)
            {
                // ctor
            }

            /**
             * Move assignment operator.
             *
             * \param other     Other hash_fn object (moved from)
             * \return          A reference to this
             */
            hash_fn& operator= (hash_fn&& other)
            {
                m_salt = other.m_salt;
                m_hash_fn = other.m_hash_fn;

                return *this;
            }

            hash_fn() : hash_fn(0) {};

            /**
             * Destructor.
             */
            ~hash_fn()
            {
                // dtor
            }
    }; // struct hash_fn
} // namespace detail
