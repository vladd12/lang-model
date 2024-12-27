#include "lang-model/ast/expr/unary.hpp"

#include <lang-model/ast/visitor.hpp>

namespace AST
{

Unary::Unary(ExpressionPtr &right, const Parse::Token &operator_) noexcept
    : Expression(), m_right(std::move(right)), m_operator(operator_)
{
}

Unary::Unary(Unary &&other) noexcept : Expression(), m_right(std::move(other.m_right)), m_operator(other.m_operator)
{
}

void Unary::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

} // namespace AST
