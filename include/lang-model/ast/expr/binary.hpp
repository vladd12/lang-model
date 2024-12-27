#pragma once

#include <lang-model/ast/expression.hpp>

namespace AST
{

class Binary final : public Expression
{
private:
  ExpressionPtr m_left;
  ExpressionPtr m_right;
  Token m_operator;

public:
  Binary() = delete;
  Binary(ExpressionPtr &left, ExpressionPtr &right, const Token operator_) noexcept;
  Binary(Binary &&other) noexcept;

  void accept(Visitor &visitor) override;
};

} // namespace AST
