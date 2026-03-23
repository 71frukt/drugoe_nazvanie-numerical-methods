#include <concepts>
#include <cstddef>
#include <vector>
namespace dumb_math                    {
namespace detail::lookup_table_builder {

struct TableItem
{
    long double one_div_x;
    long double log2_x;    
};

[[nodiscard]] std::vector<TableItem> BuildTable(const size_t teble_size)
{

}

} // namespace lookup_table_builder    
} // namespace dumb_math