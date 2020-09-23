#include <gtest/gtest.h>
#include <{{cookiecutter.repo_name}}Utils.h>

TEST(testSum, OutputTest) {
    EXPECT_EQ(4, sum(1,3));
}
