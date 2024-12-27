#include "lang-model/ast/expr/unary.hpp"

namespace AST
{

Unary::Unary(ExpressionPtr &right, const Token operator_) noexcept
    : Expression(), m_right(std::move(right)), m_operator(operator_)
{
}

Unary::Unary(Unary &&other) noexcept : Expression(), m_right(std::move(other.m_right)), m_operator(other.m_operator)
{
}

} // namespace AST
