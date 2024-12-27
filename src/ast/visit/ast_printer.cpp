#include "lang-model/ast/visit/ast_printer.hpp"

#include <lang-model/ast/expr/binary.hpp>
#include <lang-model/ast/expr/grouping.hpp>
#include <lang-model/ast/expr/literal.hpp>
#include <lang-model/ast/expr/unary.hpp>

namespace AST
{

void AstPrinter::visit(Binary &expression)
{
  ;
}

void AstPrinter::visit(Grouping &expression)
{
  ;
}

void AstPrinter::visit(Literal &expression)
{
  ;
}

void AstPrinter::visit(Unary &expression)
{
  ;
}

std::string AstPrinter::toString(Expression &expr)
{
  expr.accept(*this);
  return m_str;
}

} // namespace AST
