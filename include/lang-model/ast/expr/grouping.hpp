#pragma once

#include <lang-model/ast/expression.hpp>

namespace AST
{

class Grouping final : public Expression
{
private:
  ExpressionPtr m_expr;

public:
  Grouping() = delete;
  Grouping(ExpressionPtr &expr) noexcept;
  Grouping(Grouping &&other) noexcept;
};

} // namespace AST
