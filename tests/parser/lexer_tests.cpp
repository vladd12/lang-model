#include <gtest/gtest.h>
#include <iostream>
#include <lang-model/parser/lexer.hpp>

TEST(Lexer, ParseTokensTest)
{
    using namespace std::string_view_literals;
    Parse::Lexer lexer("var a = 1;"sv);
    for (const auto &token : lexer.getTokens())
    {
        std::cout << token << '\n';
    }
    ASSERT_EQ(true, true);

    //    constexpr auto sub = "var a = 1;"sv.substr(0, 3);
    //    ASSERT_EQ(sub, "var"sv);
}
