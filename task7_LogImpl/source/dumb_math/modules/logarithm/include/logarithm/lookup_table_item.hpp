#include <cstdint>
#include <cstring>
#include <limits>
#include <bit>
#include <concepts>

#include "get_floating_parts.hpp"

namespace dumb_math::logarithm {
namespace detail::lookup_table {

struct TableItem
{
    long double one_div_x;
    long double ln_x;    
};


template <size_t TableSizeExp, std::floating_point T>
uint32_t GetTableIndex(T x) 
{
    static_assert(TableSizeExp > 0 && TableSizeExp <= 32, "TableSizeExp is out of bounds");

    const auto mantissa = common::GetMantissa(x);
    constexpr int frac_bits = std::numeric_limits<T>::digits - 1;

    static_assert(TableSizeExp <= static_cast<size_t>(frac_bits), 
                  "TableSizeExp exceeds available fraction bits");

    const uint64_t mask = (1ULL << TableSizeExp) - 1;
    
    return static_cast<uint32_t>((mantissa >> (frac_bits - TableSizeExp)) & mask);
}

} // namespace dumb_math::logarithm
} // namespace detail::lookup_table