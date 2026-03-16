#pragma once

#include "first_level_tests/first_level_tester.hpp"
#include <cstddef>
#include <vector>

namespace rnd_generators_test {

class TwoLevelTester
{
public:
    TwoLevelTester() = default;

    TwoLevelTester(const std::vector<double> sequence)
        : sequence_(sequence)
    {}

    [[nodiscard]] double Run(const FirstLevelTester& first_lvl_tester, size_t block_count);

private:

std::span<const double> GetBlock_(size_t block_index, const size_t block_count) const;

private:

    const std::vector<double> sequence_;
};

} // namespace rnd_generators_test