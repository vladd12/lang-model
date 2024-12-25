#pragma once

#include <cstdint>

namespace Expressions
{

/// \brief Describes the node types for the nodes of an expression tree.
enum class ExpressionType : std::uint8_t
{
    Undefined = 0, ///< Undefined expression type.

    // Numeric operations.
    Add,                   ///< An addition operation, such as '(a + b)' expression, without overflow checking.
    AddChecked,            ///< An addition operation, such as '(a + b)' expression, with overflow checking.
    AddAssign,             ///< An addition operation, such as '(a += b)' expression, without overflow checking.
    AddAssignChecked,      ///< An addition operation, such as '(a += b)' expression, with overflow checking.
    Increment,             ///< An unary increment operation, such as '(a + 1)' expression.
    PreIncrementAssign,    ///< A unary prefix increment, such as '(++a)' expression.
    PostIncrementAssign,   ///< A unary postfix increment, such as '(a++)' expression.
    Subtract,              ///< A subtraction operation, such as '(a - b)' expression, without overflow checking.
    SubtractChecked,       ///< A subtraction operation, such as '(a - b)' expression, with overflow checking.
    SubtractAssign,        ///< A subtraction compound assignment operation, such as '(a -= b)' expression,
                           ///< without overflow checking.
    SubtractAssignChecked, ///< A subtraction compound assignment operation, such as '(a -= b)' expression,
                           ///< with overflow checking.
    Decrement,             ///< An unary decrement operation, such as '(a - 1)' expression.
    PreDecrementAssign,    ///< A unary prefix decrement, such as '(--a)' expression.
    PostDecrementAssign,   ///< A unary postfix decrement, such as '(a--)' expression.
    Negate,                ///< An arithmetic negation operation, such as '(-a)' expression, without overflow checking.
    NegateChecked,         ///< An arithmetic negation operation, such as '(-a)' expression, with overflow checking.
    Multiply,              ///< A multiplication operation, such as '(a * b)' expression, without overflow checking.
    MultiplyChecked,       ///< A multiplication operation, such as '(a * b)' expression, with overflow checking,
    MultiplyAssign,        ///< A multiplication compound assignment operation, such as '(a *= b)'
                           ///< expression, without overflow checking.
    MultiplyAssignChecked, ///< A multiplication compound assignment operation, such as '(a *= b)'
                           ///< expression, with overflow checking.
    Divide,                ///< A division operation, such as '(a / b)' expression.
    DivideAssign,          ///< A division compound assignment operation, such as '(a /= b)' expression.
    Modulo,                ///< An arithmetic remainder operation, such as '(a % b)' expression.
    ModuloAssign,          ///< An arithmetic remainder compound assignment operation, such as (a %= b) expression.
    Power,       ///< A mathematical operation that raises a number to a power, such as '(a ** b)' expression in Python.
    PowerAssign, ///< A compound assignment operation that raises a number to a power, such as '(a **= b)' expression.

    // Bitwise operations.
    And,               ///< A bitwise or logical AND operation, such as '(a & b)' expression.
    AndAssign,         ///< A bitwise or logical AND compound assignment operation, such as '(a &= b)' expression.
    ExclusiveOr,       ///< A bitwise or logical XOR operation, such as '(a ^ b)' expression.
    ExclusiveOrAssign, ///< A bitwise or logical XOR compound assignment operation, such as '(a ^= b)' expression.
    LeftShift,         ///< A bitwise left-shift operation, such as '(a << b)' expression.
    LeftShiftAssign,   ///< A bitwise left-shift compound assignment, such as '(a <<= b)' expression.
    RightShift,        ///< A bitwise right-shift operation, such as '(a >> b)' expression.
    RightShiftAssign,  ///< A bitwise right-shift compound assignment operation, such as '(a >>= b)' expression.
    OnesComplement,    ///< A ones complement operation, such as '(~a)' expression.
    Or,                ///< A bitwise or logical OR operation, such as '(a | b)' expression.
    OrAssign,          ///< A bitwise or logical OR compound assignment, such as '(a |= b)' expression.

    // Conditional operations.
    AndAlso, ///< A conditional AND operation, such as '(a && b)' expression.
    OrElse,  ///< A short-circuiting conditional OR operation, such as '(a || b)' expression.
    IsFalse, ///< A false condition value.
    IsTrue,  ///< A true condition value.

    // Comparison operations.
    Equal,              ///< A node that represents an equality comparison, such as '(a == b)' expression.
    NotEqual,           ///< An inequality comparison, such as '(a != b)' expression.
    LessThan,           ///< A "less than" comparison, such as '(a < b)' expression.
    LessThanOrEqual,    ///< A "less than or equal to" comparison, such as '(a <= b)' expression.
    GreaterThan,        ///< A "greater than" comparison, such as '(a > b)' expression.
    GreaterThanOrEqual, ///< A "greater than or equal to" comparison, such as '(a >= b)' expression.
    Not,                ///< A bitwise complement or logical negation operation, such as '(~a)' expression
                        ///< for integral types and such as '(!a)' for Boolean values.

    // Base language operations.
    ArrayIndex,   ///< An indexing operation in an array, such as 'array[index]' expression.
    Assign,       ///< An assignment operation, such as '(a = b)' expression.
    Block,        ///< A block of expressions, such as '{ expr1; expr2; ... }' expression.
    Call,         ///< A method call, such as 'obj.method()' expression.
    Conditional,  ///< A conditional operation, such as '(a > b) ? a : b' expression.
    Constant,     ///< A constant value.
    Goto,         ///< A "go to" expression, such as '(goto Label)' expression.
    Label,        ///< A label.
    ListInit,     ///< An operation that creates a new ListInitializer, such as '(a = {1, 2, 3})' expression.
    Loop,         ///< A loop, such as 'for' or 'while' expression.
    MemberAccess, ///< An operation that reads from a field or property, such as 'obj.property' expression.
    MemberInit,   ///< An operation that creates a new object and initializes one or more of its members,
                  ///< such as '(Point { X = 1, Y = 2 })' expression.
    ArrayBounds,  ///< An operation that creates a new array, in which the bounds for each dimension are specified,
                  ///< such as 'Type[dim1, dim2, ...]' expression.
    ArrayInit,    ///< An operation that creates a new one-dimensional array and initializes it from a list of elements,
                  ///< such as 'Type[] = {a, b, c}' expression.
    Parameter,    ///< A reference to a parameter or variable that is defined in the context of the expression.
    RuntimeVariables, ///< A list of run-time variables.
    Switch,           ///< A switch operation expression.
    Throw,            ///< An operation that throws an exception.
    Try,              ///< A try-catch expression.

    // Work with types
    Convert,        ///< A cast or conversion operation, such as '(NewType)obj' expression, without overflow checking.
    ConvertChecked, ///< A cast or conversion operation, such as '(NewType)obj' expression, with overflow checking.
    TypeAs,         ///< A boxing conversion in which null is supplied if the conversion fails,
                    ///< such as '(obj as Type)' expression.
    TypeEqual,      ///< An exact type test, such as '(obj.isType<Type>())' expression.
    TypeIs,         ///< A type test, such as '(obj is Type)' expression.
    UnboxType,      ///< An unbox value type operation, such as 'unbox' and 'unbox.any' instructions in MSIL.

    // Extended language operations.
    DebugInfo, ///< Debugging information.
    Default,   ///< A default value.
    Dynamic,   ///< A dynamic operation.
    Extension, ///< An extension expression.
    Invoke,    ///< An operation that invokes a delegate or lambda expression.
    Lambda,    ///< A lambda expression, such as '(a => (a + a))' expression.
    New,       ///< An operation that calls a constructor to create a new object, such as 'new Object()' expression.
    Quote,     ///< An expression that has a constant value of type Expression.

    // ABI non-broken
    ErrorExpression = UINT8_MAX ///< Error expression type.
};

} // namespace Expressions
