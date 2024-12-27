#pragma once

#include <boost/noncopyable.hpp>
#include <lang-model/export.hpp>

namespace AST
{

class Expression;
class Binary;
class Grouping;
class Literal;
class Unary;

class Visitor : public boost::noncopyable
{
public:
  explicit Visitor() noexcept = default;

  virtual void visit(Binary &expression) = 0;
  virtual void visit(Grouping &expression) = 0;
  virtual void visit(Literal &expression) = 0;
  virtual void visit(Unary &expression) = 0;
};

}
