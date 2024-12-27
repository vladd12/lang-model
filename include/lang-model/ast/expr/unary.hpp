#pragma once

#include <lang-model/ast/expression.hpp>

namespace AST
{

class libapi Unary final : public Expression
{
public:
  ExpressionPtr m_right;
  Token m_operator;

  Unary() = delete;
  Unary(ExpressionPtr &right, const Token &operator_) noexcept;
  Unary(Unary &&other) noexcept;

  void accept(Visitor &visitor) override;
};

} // namespace AST
