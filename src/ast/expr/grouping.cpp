#include "lang-model/ast/expr/grouping.hpp"

namespace AST
{

Grouping::Grouping(ExpressionPtr &expr) noexcept : Expression(), m_expr(std::move(expr))
{
}

Grouping::Grouping(Grouping &&other) noexcept : Expression(), m_expr(std::move(other.m_expr))
{
}

} // namespace AST
