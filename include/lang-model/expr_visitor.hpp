#pragma once

#include <memory>

namespace Expressions
{

// Forward declaration of the expression class.
class Expression;
using ExpressionPtr = std::shared_ptr<Expression>;

/// \brief Represents a visitor or rewriter for expression trees.
class ExpressionVisitor
{
public:
    void visit(Expression *expr);
};

} // namespace Expressions
