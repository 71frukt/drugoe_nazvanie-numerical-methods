#include <iostream>
#include "RLogSU/logger.hpp"

#include <dumb_math>

int main()
{
    RLSU_ASSERT(1 == 2, "хуй! {}", 99);

    dumb_math::ln(60.2);
    return 0;
}