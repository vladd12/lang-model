#include "lang-model/ast/expr/binary.hpp"

namespace AST
{

Binary::Binary(ExpressionPtr &left, ExpressionPtr &right, const Token operator_) noexcept
    : Expression(), m_left(std::move(left)), m_right(std::move(right)), m_operator(operator_)
{
}

Binary::Binary(Binary &&other) noexcept
    : Expression(), m_left(std::move(other.m_left)), m_right(std::move(other.m_right)), m_operator(other.m_operator)
{
}

} // namespace AST
