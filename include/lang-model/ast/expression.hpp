#include <boost/noncopyable.hpp>
#include <lang-model/parser/token.hpp>
#include <memory>

namespace AST
{

using Token = Parse::TokenType;

class Expression : public boost::noncopyable
{
};

using ExpressionPtr = std::unique_ptr<Expression>;
using ExpressionPtr = std::unique_ptr<Expression>;

class Binary final : public Expression
{
private:
  ExpressionPtr m_left;
  ExpressionPtr m_right;
  Token m_operator;

public:
  Binary() = delete;
  Binary(ExpressionPtr &left, ExpressionPtr &right, const Token operator_) noexcept
      : m_left(std::move(left)), m_right(std::move(right)), m_operator(operator_)
  {
  }

  Binary(Binary &&other) noexcept
      : m_left(std::move(other.m_left)), m_right(std::move(other.m_right)), m_operator(other.m_operator)
  {
  }
};

class Grouping final : public Expression
{
private:
  ExpressionPtr m_expr;

public:
  Grouping() = delete;
  Grouping(ExpressionPtr &expr) noexcept : m_expr(std::move(expr))
  {
  }

  Grouping(Grouping &&other) noexcept : m_expr(std::move(other.m_expr))
  {
  }
};

/// TODO: One class for integer, float and string literals?
// "Literal : Object value"
class Literal final : public Expression
{
};

class Unary final : public Expression
{
private:
  ExpressionPtr m_right;
  Token m_operator;

public:
  Unary() = delete;
  Unary(ExpressionPtr &right, const Token operator_) noexcept : m_right(std::move(right)), m_operator(operator_)
  {
  }

  Unary(Unary &&other) noexcept : m_right(std::move(other.m_right)), m_operator(other.m_operator)
  {
  }
};

} // namespace AST
