#include <gtest/gtest.h>

#include "mpreal.h"
#include "dumb_math/detail/calc_ulp_error.hpp"

TEST(SanityCheck, AlwaysPasses) 
{
    EXPECT_TRUE(true);
    ASSERT_EQ(1, 1);
}