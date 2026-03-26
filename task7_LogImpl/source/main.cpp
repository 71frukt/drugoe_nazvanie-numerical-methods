#include <iostream>
#include <iomanip>
#include <limits>

#include "dumb_math.hpp"

// #include "dumb_math/lib/mpreal.h"
// #include "dumb_math/detail/calc_ulp_error.hpp"

int main()
{
    // std::cout << dumb_math::logarithm::ln<long double>((long double) 0.0) << std::endl;

    long double ln = dumb_math::logarithm::ln<long double>(0.5);

    // using mpfr::mpreal;
    // mpreal::set_default_prec(256);

    // mpreal x_str = "1.1";
    // mpreal result_str = mpfr::log(x_str);

    // std::cout << std::setprecision(50);
    // std::cout << "ln(1.1) etalon = " << result_str << std::endl;
    std::cout << "ln(0.5) test   = " << ln         << std::endl;

    // std::cout << "ulps = " << dumb_math::common::CalcUlpError(ln, result_str) << std::endl;

    return 0;
}
