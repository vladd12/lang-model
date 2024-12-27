#include "lang-model/ast/expr/literal.hpp"

#include <lang-model/ast/visitor.hpp>

namespace AST
{

Literal::Literal() noexcept = default;

void Literal::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

} // namespace AST
