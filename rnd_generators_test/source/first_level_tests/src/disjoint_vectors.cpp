#include "first_level_tests/disjoint_vectors.hpp"

#include <vector>

namespace rnd_generators_test {

double DisjointVectorsTester::GetTestStatistics(std::span<const double> block) const
{
    std::vector<double> observed(baskets_count_, 0.0);

    for (double val : block)
    {
        size_t basket_indx = std::min(static_cast<size_t>(val * baskets_count_), baskets_count_ - 1);
        observed[basket_indx] += 1.0;
    }

    double expected = static_cast<double>(block.size()) / baskets_count_;
    double y_statistic = 0.0;

    for (double obs : observed)
    {
        double diff = obs - expected;
        y_statistic += (diff * diff) / expected;
    }

    return y_statistic;
}

double DisjointVectorsTester::GetCDF(double statistic_y) const
{
    return boost::math::cdf(expected_dist_, statistic_y);
}

} // namespace rnd_generators_test