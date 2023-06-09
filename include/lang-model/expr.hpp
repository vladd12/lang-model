#pragma once

#include <lang-model/export.hpp>
#include <lang-model/expr_type.hpp>
#include <lang-model/expr_visitor.hpp>

namespace Expressions
{

/// \brief The base class from which the classes that represent expression tree nodes are derived.
class libapi Expression
{
private:
    ExpressionType _nodeType;

public:
    explicit Expression(ExpressionType nodeType = ExpressionType::Undefined) noexcept;

    /// \brief Gets the node type of this expression.
    ExpressionType getNodeType() const noexcept;

    /// \brief Dispatches to the specific visit method for this node type.
    virtual ExpressionPtr accept(ExpressionVisitor &visitor) = 0;

    /// \brief Indicates that the node can be reduced to a simpler node.
    /// \return If this returns true, expression can be produced to the reduced form.
    /// \see reduce
    virtual bool canReduce() const noexcept;

    /// \brief Reduces this node to a simpler expression.
    /// \return If expression can be reduced, this should return a valid expression.
    /// \see canReduce
    virtual ExpressionPtr reduce() const = 0;
};

} // namespace Expressions
