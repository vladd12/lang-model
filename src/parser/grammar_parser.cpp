#include "lang-model/parser/grammar_parser.hpp"

#include <lang-model/ast/expr/binary.hpp>
#include <lang-model/ast/expr/grouping.hpp>
#include <lang-model/ast/expr/literal.hpp>
#include <lang-model/ast/expr/unary.hpp>
#include <lang-model/parser/parse_error.hpp>
#include <lang-model/utils/error_handler.hpp>
#include <lang-model/utils/utils.hpp>

namespace
{

::Parse::ParseError error(const ::Parse::Token &token, const std::string_view &message)
{
  ::Utils::ErrorHandler::error(token, message);
  return ::Parse::ParseError(message.data());
}

} // anonymous namespace

namespace Parse
{

/*
Expression grammar:

expression -> equality ;
equality   -> comparison ( ( "!=" | "==" ) comparison )* ;
comparison -> term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term       -> factor ( ( "-" | "+" ) factor )* ;
factor     -> unary ( ( "/" | "*" ) unary )* ;
unary      -> ( "!" | "-" ) unary
            | primary ;
primary    -> NUMBER | STRING | "true" | "false" | "nil"
            | "(" expression ")" ;
*/

GrammarParser::GrammarParser(const std::vector<Token> &tokens) noexcept : m_tokens(tokens), m_current(0)
{
}

const Token &GrammarParser::peek() const noexcept
{
  return m_tokens[m_current];
}

const Token &GrammarParser::previous() const noexcept
{
  return m_tokens[m_current - 1];
}

bool GrammarParser::isAtEnd() const noexcept
{
  return TokenType(peek()) == TokenType::EOF_;
}

const Token &GrammarParser::advance() noexcept
{
  const auto &token = peek();
  if (TokenType(token) != TokenType::EOF_)
    ++m_current;
  return token;
}

bool GrammarParser::check(const TokenType type) const noexcept
{
  if (isAtEnd())
    return false;
  else
    return TokenType(peek()) == type;
}

bool GrammarParser::match(const std::vector<TokenType> &types) noexcept
{
  for (const auto &type : types)
  {
    if (check(type))
    {
      advance();
      return true;
    }
  }
  return false;
}

const Token &GrammarParser::consume(const TokenType type, const std::string_view &message)
{
  if (check(type))
    return advance();
  throw ::error(peek(), message);
}

::AST::ExpressionPtr GrammarParser::primary()
{
  // primary    -> NUMBER | STRING | "true" | "false" | "nil"
  //             | "(" expression ")" ;
  if (match({ TokenType::INTEGER, TokenType::FLOAT, TokenType::STRING, TokenType::TRUE, TokenType::FALSE, TokenType::NIL }))
  {
    const auto &token = previous();
    switch (TokenType(token))
    {
    case TokenType::INTEGER:
      return ::AST::ExpressionPtr(new ::AST::Literal(std::stoull(token.lexeme().data())));
    case TokenType::FLOAT:
      return ::AST::ExpressionPtr(new ::AST::Literal(std::stod(token.lexeme().data())));
    case TokenType::STRING:
      return ::AST::ExpressionPtr(new ::AST::Literal(token.lexeme().data()));
    case TokenType::TRUE:
      return ::AST::ExpressionPtr(new ::AST::Literal(true));
    case TokenType::FALSE:
      return ::AST::ExpressionPtr(new ::AST::Literal(false));
    case TokenType::NIL:
      return ::AST::ExpressionPtr(new ::AST::Literal());
    default:
      throw ::error(token, "Unexpected token.");
    }
  }
  if (match({ TokenType::LEFT_PAREN }))
  {
    auto expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
    return ::AST::ExpressionPtr(new ::AST::Grouping(expr));
  }

  throw ::error(peek(), "Expect expression.");
}

::AST::ExpressionPtr GrammarParser::unary()
{
  // unary      -> ( "!" | "-" ) unary
  //             | primary ;
  if (match({ TokenType::BANG, TokenType::MINUS }))
  {
    const auto &operator_ = previous();
    auto right = unary();
    return ::AST::ExpressionPtr(new ::AST::Unary(right, operator_));
  }
  return primary();
}

::AST::ExpressionPtr GrammarParser::factor()
{
  // factor     -> unary ( ( "/" | "*" ) unary )* ;
  auto expr = unary();
  while (match({ TokenType::SLASH, TokenType::STAR }))
  {
    const auto &operator_ = previous();
    auto right = unary();
    expr.reset(new ::AST::Binary(expr, right, operator_));
  }
  return expr;
}

::AST::ExpressionPtr GrammarParser::term()
{
  // term       -> factor ( ( "-" | "+" ) factor )* ;
  auto expr = factor();
  while (match({ TokenType::MINUS, TokenType::PLUS }))
  {
    const auto &operator_ = previous();
    auto right = factor();
    expr.reset(new ::AST::Binary(expr, right, operator_));
  }
  return expr;
}

::AST::ExpressionPtr GrammarParser::comparison()
{
  // comparison -> term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
  auto expr = term();
  while (match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL }))
  {
    const auto &operator_ = previous();
    auto right = term();
    expr.reset(new ::AST::Binary(expr, right, operator_));
  }
  return expr;
}

::AST::ExpressionPtr GrammarParser::equality()
{
  // equality   -> comparison ( ( "!=" | "==" ) comparison )* ;
  auto expr = comparison();
  while (match({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL }))
  {
    const auto &operator_ = previous();
    auto right = comparison();
    expr.reset(new ::AST::Binary(expr, right, operator_));
  }
  return expr;
}

::AST::ExpressionPtr GrammarParser::expression()
{
  // expression -> equality ;
  return equality();
}

} // namespace Parse
