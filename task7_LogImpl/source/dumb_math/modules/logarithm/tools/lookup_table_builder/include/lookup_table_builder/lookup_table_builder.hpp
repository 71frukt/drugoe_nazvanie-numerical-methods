#pragma once

#include <iostream>
#include <ostream>
#include <vector>

namespace dumb_math::logarithm {
namespace detail::lookup_table {

#define LN_LOOKUP_TABLE  LookupTable

struct TableItem
{
    long double one_div_x;
    long double ln_x;    
};

[[nodiscard]] std::vector<TableItem> BuildTable(const size_t table_size_exp);

void PrintTable(const std::vector<TableItem>& table, std::ostream& ostream);

} // namespace detail::lookup_table 
} // namespace dumb_math::logarithm