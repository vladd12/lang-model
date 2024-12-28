#include "lang-model/ast/expr/literal.hpp"

#include <lang-model/ast/visitor.hpp>

namespace AST
{

Literal::Literal() noexcept : Expression()
{
}

Literal::Literal(const std::uint64_t value) noexcept : Expression(), m_value(value)
{
}

Literal::Literal(const std::int64_t value) noexcept : Expression(), m_value(value)
{
}

Literal::Literal(const double value) noexcept : Expression(), m_value(value)
{
}

Literal::Literal(const std::string &value) : Expression(), m_value(value)
{
}

Literal::Literal(const char value) noexcept : Expression(), m_value(value)
{
}

Literal::Literal(const bool value) noexcept : Expression(), m_value(value)
{
}

Literal::holder_type &Literal::get() noexcept
{
  return m_value;
}

const Literal::holder_type &Literal::get() const noexcept
{
  return m_value;
}

void Literal::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

} // namespace AST
