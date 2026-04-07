#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <boost/math/distributions/kolmogorov_smirnov.hpp>

struct SawtoothGenerator
{
    double current = 0.0;
    double step;

    SawtoothGenerator(size_t n) : step(1.0 / static_cast<double>(n)) {}

    double next() {
        double val = current;
        current += step;
        if (current >= 1.0) current = 0.0;
        return val;
    }
};

double RunSimpleKSTest(std::vector<double>& data)
{
    size_t n = data.size();
    std::sort(data.begin(), data.end());

    double max_diff = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double empirical_cdf = static_cast<double>(i + 1) / n;
        double theoretical_cdf = data[i];
        
        double diff = std::abs(empirical_cdf - theoretical_cdf);
        if (diff > max_diff) max_diff = diff;
    }
    return max_diff;
}

int main()
{
    const size_t n = 1000;
    SawtoothGenerator gen(n);
    std::vector<double> data(n);

    for (size_t i = 0; i < n; ++i) {
        data[i] = gen.next();
    }

    double dn = RunSimpleKSTest(data);
    
    boost::math::kolmogorov_smirnov_distribution<double> dist(static_cast<double>(n));

    // p-value === вероятность того что случайная величина примет 
    // значение >= наблюдаемому dn
    double p_value = boost::math::cdf(boost::math::complement(dist, dn));

    std::cout << "KS Statistic (Dn): " << dn << std::endl;
    std::cout << "P-Value:           " << p_value << std::endl;

    return 0;
}