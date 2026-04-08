#include "clogf.h"
#include "logarithm/logarithm.hpp"

extern "C" float logf(float x)
{
    return dumb_math::logarithm::ln<float>(x);
}