#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <cstring>
#include <functional>
#include <limits>
#include <random>
#include <type_traits>

#include "byte_conv.hpp"
#include "hash_fn.hpp"

#pragma once

/**
 * Class implementing a bloom filter. A bloom filter gets added a set of values
 * and can then say whether a value is maybe in the set or is guaranteed not to
 * be.
 *
 * This works as follows: A set of hash functions, such that ideally all hashes
 * of one object are distinct, are used to hash items added to the set. The
 * indices in a bitset corresponding to the hash values (e.g. hash 0101 ->
 * index 5) are set to true. Now, to check whether an item is in the set, again
 * it is hashed with all functions. If all corresponding bits are set, the item
 * is <i>maybe</i> in the set. If not all bits are set, the item is
 * <i>guaranteed</i> not to be in the set.
 *
 * The <code>num_hash_functions</code> and <code>hash_precision</code>
 * parameters can be tuned for a good compromise between precision of tests
 * (few false positives) and storage and runtime. The rule for good
 * <code>std::hash</code> implementations is that for a desired false positive
 * rate <i>p</i> and a number of inserted elements <i>n</i> we have:
 *
 * \f[
 *      \mathrm{num\_hash\_functions} = -\log_2(p)
 * \f]
 *
 * and
 *
 * \f[
 *      \mathrm{hash\_precision} = \frac{n \cdot \ln(p)}{\left( \ln(2) \right)^2}
 * \f]
 *
 * \param T             Template parameter for the type to build the filter for.
 * \param num_hash_functions The number of hash functions to use for fingerprints.
 * \param hash_precision    The number of bits to use for the fingerprints.
 * Keep in mind that using few bits here will lead to very imprecise results
 * (many false positives). Also keep in mind using many bits will drastically
 * increase the storage requirements of objects of this class. The hash
 * precision may not be more precise than the number of bits in a
 * <code>size_t</code> for obvious reasons.
 */
template<typename T, size_t num_hash_functions, size_t hash_precision>
class bloom_filter
{
    public:
        /**
         * Constructor. Initializes all hash function with (pseudo)random salt
         * values.
         */
        bloom_filter()
        :   m_hash_functions(),
            m_hash_hits()
        {
            // choose salt uniform at random from [ 0, 2^{63} ]
            std::default_random_engine generator;
            std::uniform_int_distribution<size_t> distribution (
                    0,
                    std::numeric_limits<size_t>::max()
                );
            for (size_t i = 0; i < num_hash_functions; ++i)
            {
                auto const salt { distribution(generator) };
                m_hash_functions[i] = detail::hash_fn<hash_precision>(salt);
            }
        };

        /**
         * Destructor.
         */
        ~bloom_filter() = default;

        /**
         * Add a value to the filter. This hashes the value with all hash
         * functions and sets the respective bits in the bitset.
         *
         * \param t     Value to add
         */
        void add(T const& t)
        {
            // reduce to sizeof(size_t) bytes
            size_t const val = detail::reduce_object(t);
            for (auto& fn : m_hash_functions)
            {
                auto hash = fn(val);
                m_hash_hits.set(hash.to_ulong());
            }
        };

        /**
         * Test whether a value is in the filter. The return value
         * <code>false</code> means that the value is <i>guaranteed</i> not to
         * be in the filter. The return value <code>true</code> means that the
         * value <i>maybe</i> is in the set.
         *
         * \param t     Data item to check for
         * \return      Boolean value indicating membership
         */
        bool test(T const& t)
        {
            // reduce bytes of t to one size_t
            size_t const val = detail::reduce_object(t);

            // t may be member if the indices of all hashes of the value are
            // set in the bitset
            return std::all_of(
                    m_hash_functions.begin(),
                    m_hash_functions.end(),
                    [&](detail::hash_fn<hash_precision>& fn)
                    {
                        return m_hash_hits.test(fn(val).to_ulong());
                    }
                );
        };

    private:
        /**
         * The array of hash functions. All hash functions ideally should have
         * different salt values. This is currently not enforced.
         */
        std::array<detail::hash_fn<hash_precision>, num_hash_functions>
            m_hash_functions;

        /**
         * The bitset of hash function hits. The result space of the hash
         * functions is a bitset of size <code>hash_precision</code>, so the
         * bitset of hits has a size of $2^{hash_precision}$ to have an entry
         * for each possible return value.
         */
        std::bitset<(1ul<<hash_precision)> m_hash_hits;
};

