#pragma once

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <span>

#include "RLogSU/logger.hpp"

namespace rnd_generators_test {

class FirstLevelTester
{
public:

    [[nodiscard]] virtual double GetTestStatistics(std::span<const double> block) const = 0;
    [[nodiscard]] virtual double GetCDF           (double statistic_y)            const = 0;
    
private:

    [[nodiscard]] bool VerifyTestedBlock_(std::span<const double> tested_block) const
    {
        for (double item : tested_block)
        {
            if (item < 0 || item > 1)
                return false;
        }

        return true;
    }
};

} // namespace rnd_generators_test