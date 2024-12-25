#include <array>
#include <gtest/gtest.h>
#include <lang-model/parser/scanner.hpp>

TEST(Scanner, OperatorsTest)
{
  std::array<Parse::TokenType, 19> expected_tokens {
    Parse::TokenType::LEFT_PAREN, Parse::TokenType::LEFT_PAREN,    //
    Parse::TokenType::RIGHT_PAREN, Parse::TokenType::RIGHT_PAREN,  //
    Parse::TokenType::LEFT_BRACE, Parse::TokenType::RIGHT_BRACE,   //
    Parse::TokenType::BANG, Parse::TokenType::STAR,                //
    Parse::TokenType::PLUS, Parse::TokenType::MINUS,               //
    Parse::TokenType::SLASH, Parse::TokenType::EQUAL,              //
    Parse::TokenType::LESS, Parse::TokenType::GREATER,             //
    Parse::TokenType::LESS_EQUAL, Parse::TokenType::GREATER_EQUAL, //
    Parse::TokenType::EQUAL_EQUAL, Parse::TokenType::BANG_EQUAL,   //
    Parse::TokenType::EOF_                                         //
  };

  Parse::Scanner scanner;
  auto result = scanner.scan(R"(
    // this is a comment
    (( )){} // grouping stuff
    !*+-/=<> <= >= == != // operators
    )");
  ASSERT_EQ(result.size(), expected_tokens.size());
  for (std::size_t index = 0; index < expected_tokens.size(); ++index)
  {
    ASSERT_EQ(Parse::TokenType(result[index]), expected_tokens[index]);
  }
}

TEST(Scanner, MultyLineTest)
{
  std::array<Parse::TokenType, 4> expected_tokens {
    Parse::TokenType::MINUS, Parse::TokenType::PLUS, //
    Parse::TokenType::STAR, Parse::TokenType::EOF_   //
  };

  Parse::Scanner scanner;
  auto result = scanner.scan(R"(
    -
    // -+
    +
    /*
    111
    *-/+
    !*+-/=<>
    */*
    )");
  ASSERT_EQ(result.size(), expected_tokens.size());
  for (std::size_t index = 0; index < expected_tokens.size(); ++index)
  {
    ASSERT_EQ(Parse::TokenType(result[index]), expected_tokens[index]);
  }
}

TEST(Scanner, VarExprTest)
{
  Parse::Scanner scanner;
  auto result = scanner.scan(R"(
    var a = 1.1
    )");
  ASSERT_TRUE(result.size() > 0);
  ASSERT_EQ(Parse::TokenType(result.back()), Parse::TokenType::EOF_);
}
