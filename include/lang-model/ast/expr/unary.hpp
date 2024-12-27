#pragma once

#include <lang-model/ast/expression.hpp>

namespace AST
{

class Unary final : public Expression
{
private:
  ExpressionPtr m_right;
  Token m_operator;

public:
  Unary() = delete;
  Unary(ExpressionPtr &right, const Token operator_) noexcept;
  Unary(Unary &&other) noexcept;
};

} // namespace AST
