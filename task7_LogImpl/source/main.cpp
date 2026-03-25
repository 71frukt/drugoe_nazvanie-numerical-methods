#include <iostream>
#include "RLogSU/logger.hpp"
#include "logarithm/logarithm.hpp"
#include "logarithm/tailor.hpp"
#include <iomanip>

#include <dumb_math>

int main()
{
    std::cout << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10);

    std::cout << dumb_math::logarithm::ln<long double>((long double) 0.0) << std::endl;
    std::cout << dumb_math::logarithm::ln<long double>((long double) 1.0) << std::endl;
    std::cout << dumb_math::logarithm::ln<long double>((long double) 2.0) << std::endl;
    std::cout << dumb_math::logarithm::ln<long double>((long double) 3.0) << std::endl;
    std::cout << dumb_math::logarithm::ln<long double>((long double) 4.0) << std::endl;
    std::cout << dumb_math::logarithm::ln<long double>((long double) 5.0) << std::endl;
    std::cout << dumb_math::logarithm::ln<long double>((long double) 6.0) << std::endl;


    return 0;
}