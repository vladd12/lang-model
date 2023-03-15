#include <lang-model/expr.hpp>

namespace Expressions
{

Expression::Expression(ExpressionType nodeType) noexcept : _nodeType(nodeType)
{
}

ExpressionType Expression::getNodeType() const noexcept
{
    return _nodeType;
}

bool Expression::canReduce() const noexcept
{
    return false;
}

} // namespace Expressions
