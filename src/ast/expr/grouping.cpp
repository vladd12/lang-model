#include "lang-model/ast/expr/grouping.hpp"

#include <lang-model/ast/visitor.hpp>

namespace AST
{

Grouping::Grouping(ExpressionPtr &expr) noexcept : Expression(), m_expr(std::move(expr))
{
}

Grouping::Grouping(Grouping &&other) noexcept : Expression(), m_expr(std::move(other.m_expr))
{
}

void Grouping::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

} // namespace AST
