#include <gtest/gtest.h>
#include <iostream>
#include <lang-model/parser/tokenizer.hpp>

// Function for debug purposes
void debugPrint(const std::vector<std::string_view> &tokens)
{
  // Debug purposes
  std::cout << "Tokens: ";
  for (const auto &token : tokens)
  {
    std::cout << '\'' << token << "\' ";
  }
  std::cout << '\n';
}

TEST(Tokenizer, ParseTokensTest_01)
{
  using namespace std::string_view_literals;
  Parse::Tokenizer tokenizer("var a = 1;"sv);
  const auto &tokens = tokenizer.getTokens();
  ASSERT_EQ(5, tokens.size()); // Tokens: 'var', 'a', '=', '1', ';'
  ASSERT_EQ("var"sv, tokens[0]);
  ASSERT_EQ("a"sv, tokens[1]);
  ASSERT_EQ("="sv, tokens[2]);
  ASSERT_EQ("1"sv, tokens[3]);
  ASSERT_EQ(";"sv, tokens[4]);
}

TEST(Tokenizer, ParseTokensTest_02)
{
  using namespace std::string_view_literals;
  Parse::Tokenizer tokenizer("var a=(1+2)*5;"sv);
  const auto &tokens = tokenizer.getTokens();
  debugPrint(tokens);

  ASSERT_EQ(11, tokens.size()); // Tokens: 'var', 'a', '=', '(', '1', '+', '2', ')', '*', '5', ';'
  ASSERT_EQ("var"sv, tokens[0]);
  ASSERT_EQ("a"sv, tokens[1]);
  ASSERT_EQ("="sv, tokens[2]);
  ASSERT_EQ("("sv, tokens[3]);
  ASSERT_EQ("1"sv, tokens[4]);
  ASSERT_EQ("+"sv, tokens[5]);
  ASSERT_EQ("2"sv, tokens[6]);
  ASSERT_EQ(")"sv, tokens[7]);
  ASSERT_EQ("*"sv, tokens[8]);
  ASSERT_EQ("5"sv, tokens[9]);
  ASSERT_EQ(";"sv, tokens[10]);
}

TEST(Tokenizer, ParseTokensTest_03)
{
  using namespace std::string_view_literals;
  Parse::Tokenizer tokenizer("   var   \t\t\t\t   a  = \n\n\n    1;;"sv);
  const auto &tokens = tokenizer.getTokens();
  ASSERT_EQ(6, tokens.size()); // Tokens: 'var', 'a', '=', '1', ';', ';'
  ASSERT_EQ("var"sv, tokens[0]);
  ASSERT_EQ("a"sv, tokens[1]);
  ASSERT_EQ("="sv, tokens[2]);
  ASSERT_EQ("1"sv, tokens[3]);
  ASSERT_EQ(";"sv, tokens[4]);
  ASSERT_EQ(";"sv, tokens[5]);
}

TEST(Tokenizer, ParseTokensTest_04)
{
  using namespace std::string_view_literals;
  Parse::Tokenizer tokenizer(";+++;"sv);
  const auto &tokens = tokenizer.getTokens();
  ASSERT_EQ(5, tokens.size()); // Tokens: ';', '+', '+', '+', ';'
  ASSERT_EQ(";"sv, tokens[0]);
  ASSERT_EQ("+"sv, tokens[1]);
  ASSERT_EQ("+"sv, tokens[2]);
  ASSERT_EQ("+"sv, tokens[3]);
  ASSERT_EQ(";"sv, tokens[4]);
}
