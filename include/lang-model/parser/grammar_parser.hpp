#pragma once

#include <lang-model/ast/expression.hpp>
#include <vector>

namespace Parse
{

/// @brief Recursive Descent Parser
class libapi GrammarParser final
{
private:
  const std::vector<Token> &m_tokens;
  std::size_t m_current;

  [[nodiscard]] const Token &peek() const noexcept;
  [[nodiscard]] const Token &previous() const noexcept;
  [[nodiscard]] bool isAtEnd() const noexcept;
  const Token &advance() noexcept;
  [[nodiscard]] bool check(const TokenType type) const noexcept;
  [[nodiscard]] bool match(const std::vector<TokenType> &types) noexcept;

  [[nodiscard]] ::AST::ExpressionPtr primary();
  [[nodiscard]] ::AST::ExpressionPtr unary();
  [[nodiscard]] ::AST::ExpressionPtr factor();
  [[nodiscard]] ::AST::ExpressionPtr term();
  [[nodiscard]] ::AST::ExpressionPtr comparison();
  [[nodiscard]] ::AST::ExpressionPtr equality();
  [[nodiscard]] ::AST::ExpressionPtr expression();

public:
  explicit GrammarParser() = delete;
  explicit GrammarParser(const std::vector<Token> &tokens) noexcept;
};

} // namespace Parse
