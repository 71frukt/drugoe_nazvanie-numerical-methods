#include <gtest/gtest.h>

TEST(SanityCheck, AlwaysPasses) 
{
    EXPECT_TRUE(true);
    ASSERT_EQ(1, 1);
}