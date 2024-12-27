#pragma once

#include <boost/noncopyable.hpp>
#include <lang-model/parser/token.hpp>
#include <memory>

namespace AST
{

using Token = Parse::TokenType;

class Visitor;

class Expression : public boost::noncopyable
{
public:
  explicit Expression() noexcept = default;

  virtual void accept(Visitor &visitor) = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;
using ExpressionPtr = std::unique_ptr<Expression>;

} // namespace AST
