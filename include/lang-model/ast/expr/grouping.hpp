#pragma once

#include <lang-model/ast/expression.hpp>

namespace AST
{

class libapi Grouping final : public Expression
{
public:
  ExpressionPtr m_expr;

  Grouping() = delete;
  Grouping(ExpressionPtr &expr) noexcept;
  Grouping(Grouping &&other) noexcept;

  void accept(Visitor &visitor) override;
};

} // namespace AST
