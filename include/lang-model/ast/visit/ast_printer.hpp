#pragma once

#include <lang-model/ast/visitor.hpp>
#include <string>

namespace AST
{

class libapi AstPrinter final : public Visitor
{
private:
  std::string m_str;

public:
  explicit AstPrinter() noexcept = default;

  void visit(Binary &expression) override;
  void visit(Grouping &expression) override;
  void visit(Literal &expression) override;
  void visit(Unary &expression) override;

  std::string toString(Expression &expr);
};

} // namespace AST
