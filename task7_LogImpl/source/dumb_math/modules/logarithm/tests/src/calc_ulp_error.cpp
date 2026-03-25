#include "logarithm/logarithm.hpp"

#include <iostream>
#include <iomanip>
#include "mpreal.h"

namespace dumb_math::logarithm {
namespace tests {


using mpfr::mpreal;

int test() 
{
    // Установка аппаратной точности в 256 бит (по умолчанию 53)
    mpreal::set_default_prec(256);

    // Инициализация через строку избегает ошибки округления формата double
    mpreal x = "1.5";
    mpreal reference_log = mpfr::log(x);

    std::cout << std::setprecision(50) 
              << "MPFR log(1.5): " << reference_log << std::endl;

    return 0;
}

} // namespace tests
} // namespace dumb_math::logarithm
