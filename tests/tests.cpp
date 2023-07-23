#include <gtest/gtest.h>

TEST(MultiplyTests, TestIntegerOne)
{
    constexpr auto a = 25;
    constexpr auto b = 100;
    constexpr auto expected = 2500;
    constexpr auto actual = a * b;
    ASSERT_EQ(expected, actual);
}
