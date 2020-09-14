#include <gtest/gtest.h>
#include <{{cookiecutter.repo_name}}_utils.h>

TEST(testSum, OutputTest) {
    EXPECT_EQ(4, sum(1,3));
}
