#include <cstdint>
#include <unordered_set>

/**
 * Simple type to be used for hashing with a salt value.
 */
template<typename T,
    typename = typename std::hash<T>::result_type>
struct salted_type
{
    T value;
    std::size_t salt;
};

namespace std
{
    template<typename T>
    struct hash<salted_type<T>>
    {
        using argument_type = salted_type<T>;
        using result_type = std::size_t;

        result_type
        operator()(argument_type const& arg) const noexcept
        {
            result_type saltable = std::hash<T>{}(arg.value);
            saltable ^= arg.salt;
            return std::hash<result_type>{}(saltable);
        }
    };
}
