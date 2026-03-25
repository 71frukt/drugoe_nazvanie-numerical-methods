#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <concepts>
#include <stdexcept>

#include "RLogSU/logger.hpp"
#include "lookup_table.hpp"
#include "logarithm/tailor.hpp"


namespace dumb_math::logarithm {

template <std::floating_point T, size_t TailorDeg = 4>
T ln(T x)
{
    if (x <= 0)
        RLSU_THROW<std::runtime_error>(RLSU_FORMAT("x={} is out of range", x));

    constexpr static long double ln2 = 0.693147180559945309417;

    using namespace logarithm::detail::lookup_table;    

    const uint32_t table_index = GetTableIndex<TableSizeExp>(x);
    const auto     mantissa    = common::GetNormalizedMantissa(x);
    const uint64_t exponenta   = common::GetExponent(x);

    T v = LookupTable[table_index].one_div_x * T(mantissa);

    T ln_x = exponenta * ln2 + LookupTable[table_index].ln_x + TailorLn<TailorDeg>(v);

    return ln_x;
}

} // namespace dumb_math::logarithm