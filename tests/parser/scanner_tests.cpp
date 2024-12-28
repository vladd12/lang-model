#include <array>
#include <gtest/gtest.h>
#include <lang-model/parser/scanner.hpp>

TEST(Scanner, OperatorsTest)
{
  using namespace ::Parse;
  std::array<TokenType, 19> expected_tokens {
    TokenType::LEFT_PAREN, TokenType::LEFT_PAREN,    //
    TokenType::RIGHT_PAREN, TokenType::RIGHT_PAREN,  //
    TokenType::LEFT_BRACE, TokenType::RIGHT_BRACE,   //
    TokenType::BANG, TokenType::STAR,                //
    TokenType::PLUS, TokenType::MINUS,               //
    TokenType::SLASH, TokenType::EQUAL,              //
    TokenType::LESS, TokenType::GREATER,             //
    TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL, //
    TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL,   //
    TokenType::EOF_                                  //
  };

  Scanner scanner;
  auto result = scanner.scan(R"(
    // this is a comment
    (( )){} // grouping stuff
    !*+-/=<> <= >= == != // operators
  )");
  ASSERT_EQ(result.size(), expected_tokens.size());
  for (std::size_t index = 0; index < expected_tokens.size(); ++index)
  {
    ASSERT_EQ(TokenType(result[index]), expected_tokens[index]);
  }
}

TEST(Scanner, MultyLineTest)
{
  using namespace ::Parse;
  std::array<TokenType, 4> expected_tokens {
    TokenType::MINUS, TokenType::PLUS, //
    TokenType::STAR, TokenType::EOF_   //
  };

  Scanner scanner;
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
    ASSERT_EQ(TokenType(result[index]), expected_tokens[index]);
  }
}

TEST(Scanner, KeywordsTest)
{
  using namespace ::Parse;
  std::array<TokenType, 17> expected_tokens {
    TokenType::IF, TokenType::ELSE, TokenType::TRUE,     //
    TokenType::FALSE, TokenType::AND, TokenType::OR,     //
    TokenType::FOR, TokenType::WHILE, TokenType::VAR,    //
    TokenType::NIL, TokenType::PRINT, TokenType::RETURN, //
    TokenType::FUN, TokenType::CLASS, TokenType::THIS,   //
    TokenType::SUPER, TokenType::EOF_                    //
  };

  Parse::Scanner scanner;
  auto result = scanner.scan(R"(
    if else true false and or for while var
    nil print return fun class this super
  )");
  ASSERT_EQ(result.size(), expected_tokens.size());
  for (std::size_t index = 0; index < expected_tokens.size(); ++index)
  {
    ASSERT_EQ(TokenType(result[index]), expected_tokens[index]);
  }
}

TEST(Scanner, VarExprTest)
{
  using namespace ::Parse;
  Scanner scanner;
  auto result = scanner.scan(R"(
    var a = 1.1
    )");
  ASSERT_TRUE(result.size() > 0);
  ASSERT_EQ(TokenType(result.back()), TokenType::EOF_);
}
