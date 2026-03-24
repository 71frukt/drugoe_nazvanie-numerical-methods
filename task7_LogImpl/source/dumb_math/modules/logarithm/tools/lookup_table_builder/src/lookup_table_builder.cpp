#include <cmath>
#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <vector>

#include "RLogSU/include/RLogSU/logger.hpp"
#include "RLogSU/logger.hpp"

#include "lookup_table_builder/lookup_table_builder.hpp"

namespace dumb_math::logarithm {
namespace detail::lookup_table {

static long double LnArctgTailor_1to2(long double x);

[[nodiscard]] std::vector<TableItem> BuildTable(const size_t table_size_exp)
{
    if (table_size_exp > 63)
    {
        RLSU_THROW<std::runtime_error>("too large table_size_exp, table_size overflow!");
    }

    size_t table_size = size_t(1) << table_size_exp;
    std::vector<TableItem> table(table_size);

    long double delta = 1 / (long double) table_size;
    long double x_i   = 1 + delta / 2;

    for (size_t i = 0; i < table_size; ++i, x_i += delta)
    {
        table[i].one_div_x = 1 / x_i;
        table[i].ln_x      = LnArctgTailor_1to2(x_i);
    }

    return table;
}

static long double LnArctgTailor_1to2(long double x)
{
    RLSU_ASSERT((x < 2) && (x >= 1), "value (x = {}) outside the segment [1; 2)", x);

    long double y0    = (x - 1) / (x + 1);
    long double yi    = y0;
    long double y0_sq = y0 * y0;
    // ln(x) = 2 * sum{n = 0, inf} (y^(2n + 1) / (2n + 1))

    long double raw      = y0;
    long double prev_raw = 0;

    for (size_t k = 1; raw != prev_raw; k++)    // until the next member of the row becomes less than ULP
    {
        prev_raw = raw;

        yi *= y0_sq;
        raw += yi / (2 * k + 1);
    }

    return raw * 2;
}

} // namespace detail::lookup_table    
} // namespace dumb_math::logarithm