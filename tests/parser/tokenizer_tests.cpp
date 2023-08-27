#include <gtest/gtest.h>
#include <iostream>
#include <lang-model/parser/tokenizer.hpp>

TEST(Tokenizer, ParseTokensTest_01)
{
    using namespace std::string_view_literals;
    Parse::Tokenizer tokenizer("var a = 1;"sv);
    const auto &tokens = tokenizer.getTokens();

    // Debug purposes
    std::cout << "Tokens: ";
    for (const auto &token : tokens)
    {
        std::cout << '\'' << token << "\' ";
    }
    std::cout << '\n';

    ASSERT_EQ(5, tokens.size()); // Tokens: 'var', 'a', '=', '1' and ';'
    ASSERT_EQ("var"sv, tokens[0]);
    ASSERT_EQ("a"sv, tokens[1]);
    ASSERT_EQ("="sv, tokens[2]);
    ASSERT_EQ("1"sv, tokens[3]);
    ASSERT_EQ(";"sv, tokens[4]);
}
