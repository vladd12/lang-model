#pragma once

#include <lang-model/ast/expression.hpp>

namespace AST
{

class libapi Binary final : public Expression
{
public:
  ExpressionPtr m_left;
  ExpressionPtr m_right;
  Token m_operator;

  Binary() = delete;
  Binary(ExpressionPtr &left, ExpressionPtr &right, const Token &operator_) noexcept;
  Binary(Binary &&other) noexcept;

  void accept(Visitor &visitor) override;
};

} // namespace AST
