#include <gtest/gtest.h>
#include <tools.h>

TEST(testSum, OutputTest) {
    EXPECT_EQ(4, sum(1,3));
}
