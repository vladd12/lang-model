#pragma once

#include <lang-model/ast/expression.hpp>

namespace AST
{

/// TODO: One class for integer, float and string literals?
// "Literal : Object value"
class Literal final : public Expression
{
public:
  Literal() noexcept;
};

} // namespace AST
