#include "first_level_tests/ifirst_level_tester.hpp"

#include <iostream>
#include <cassert>
#include <boost/math/distributions/chi_squared.hpp>

namespace rnd_generators_test {

class DisjointVectorsTester : IFirstLevelTester
{
public:
    explicit DisjointVectorsTester(size_t baskets_count)
        : baskets_count_  (baskets_count)
        , expected_dist_(baskets_count - 1)
    {
        assert(baskets_count > 1);
    }

    [[nodiscard]] double GetTestStatistics(std::span<const double> block) const override;
    [[nodiscard]] double GetCDF           (double statistic_y)            const override;

private:
    const size_t baskets_count_;
    const boost::math::chi_squared expected_dist_;
};

} // namespace rnd_generators_test