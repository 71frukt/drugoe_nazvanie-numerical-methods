#include "first_level_tests/fourier_tester.hpp"
#include "utils/bounds_check.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>

namespace rnd_generators_test {

double FourierTester::GetTestStatistics(std::span<const double> block) const
{
    size_t n = std::min(block.size(), block_size_2_deg_);
    std::vector<std::complex<double>> f(n);

    for (size_t i = 0; i < n; ++i)
    {
        f[i] = std::complex<double>(block[i] > 0.5 ? 1.0 : -1.0, 0.0);
    }

    PerformFFT_(f);

    double h = std::sqrt(2.995732274 * n);
    size_t count = 0;
    
    for (size_t i = 0; i < n / 2; ++i)
    {
        if (std::abs(f[i]) < h)
        {
            count++;
        }
    }

    return static_cast<double>(count);
}

double FourierTester::GetCDF(double statistic_y) const
{
    double n = static_cast<double>(block_size_2_deg_);
    double mu = 0.95 * n / 2.0;
    double sigma = std::sqrt(n * 0.95 * 0.05 / 4.0);

    boost::math::normal_distribution<double> dist(mu, sigma);
    return boost::math::cdf(dist, statistic_y);
}

void FourierTester::PerformFFT_(std::vector<std::complex<double>>& a) const
{
    size_t n = a.size();
    if (n <= 1) return;

    std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
    for (size_t i = 0; i * 2 < n; ++i) {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }

    PerformFFT_(a0);
    PerformFFT_(a1);

    double angle = 2 * M_PI / n;
    std::complex<double> w(1), wn(std::cos(angle), std::sin(angle));
    for (size_t i = 0; i * 2 < n; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }
}

} // namespace rnd_generators_test