#include <cmath>
#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <vector>

#include "RLogSU/include/RLogSU/logger.hpp"
#include "RLogSU/logger.hpp"

#include "lookup_table_builder/lookup_table_builder.hpp"
#include "logarithm/common/approx.hpp"

namespace dumb_math::logarithm {
namespace detail::lookup_table {

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
        table[i].ln_x      = common::LnArtgTailorBestAcc_0to2(x_i);
    }

    return table;
}

} // namespace detail::lookup_table    
} // namespace dumb_math::logarithm