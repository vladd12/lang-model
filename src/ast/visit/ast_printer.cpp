#include "lang-model/ast/visit/ast_printer.hpp"

#include <fmt/core.h>
#include <lang-model/ast/expr/binary.hpp>
#include <lang-model/ast/expr/grouping.hpp>
#include <lang-model/ast/expr/literal.hpp>
#include <lang-model/ast/expr/unary.hpp>
#include <lang-model/utils/utils.hpp>

namespace AST
{

void AstPrinter::visit(Binary &expression)
{
  m_str += fmt::format("({0} ", expression.m_operator.lexeme());
  expression.m_left->accept(*this);
  m_str += " ";
  expression.m_right->accept(*this);
  m_str += ")";
}

void AstPrinter::visit(Grouping &expression)
{
  m_str += "(group ";
  expression.m_expr->accept(*this);
  m_str += ")";
}

void AstPrinter::visit(Literal &expression)
{
  std::visit( //
    ::Utils::overloaded {
      [this](const std::uint64_t value) { m_str += std::to_string(value); },
      [this](const std::int64_t value) { m_str += std::to_string(value); },
      [this](const double value) { m_str += std::to_string(value); },
      [this](const char value) { m_str += fmt::format("'{0}'", value); },
      [this](const std::string &value) { m_str += fmt::format("'{0}'", value); },
      [this](const bool value) {
        if (value)
          m_str += "true";
        else
          m_str += "false";
      },
    },
    expression.get());
}

void AstPrinter::visit(Unary &expression)
{
  m_str += fmt::format("({0} ", expression.m_operator.lexeme());
  expression.m_right->accept(*this);
  m_str += ")";
}

std::string AstPrinter::toString(Expression &expr)
{
  std::string result;
  expr.accept(*this);
  std::swap(result, m_str);
  return result;
}

} // namespace AST
