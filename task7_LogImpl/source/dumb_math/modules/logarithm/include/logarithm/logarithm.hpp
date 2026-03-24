#pragma once

#include <iostream>
#include <concepts>

namespace dumb_math {

template <std::floating_point T>
T ln(T x)
{
    std::cout << x << std::endl;
    return x;
}

} // namespace dumb_math