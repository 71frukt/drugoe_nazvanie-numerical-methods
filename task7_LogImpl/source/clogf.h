#include "dumb_math.hpp"
#include "logarithm/logarithm.hpp"

inline float logf(float x)
{
    return dumb_math::logarithm::ln<float>(x);
}