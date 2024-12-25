#pragma once

#include <lang-model/expr.hpp>

namespace Expressions
{

template <class T> //
class ConstantExpression : public Expression
{
private:
    T _value;

public:
    ConstantExpression(const T &value) : Expression(ExpressionType::Constant), _value(value)
    {
    }
};

} // namespace Expressions
