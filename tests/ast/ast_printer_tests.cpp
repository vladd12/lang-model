#include <gtest/gtest.h>
#include <lang-model/ast/expr/binary.hpp>
#include <lang-model/ast/expr/grouping.hpp>
#include <lang-model/ast/expr/literal.hpp>
#include <lang-model/ast/expr/unary.hpp>
#include <lang-model/ast/visit/ast_printer.hpp>

TEST(AstPrinter, PlusExprTest)
{
  using namespace AST;
  AstPrinter printer;
  ExpressionPtr left(new Literal(1ull));
  ExpressionPtr right(new Literal(2ull));
  auto expr = std::make_unique<Binary>(left, right, Token { Parse::TokenType::PLUS, "+", 1 });
  auto result = printer.toString(*expr);
  ASSERT_EQ(result, "(+ 1 2)");
}

TEST(AstPrinter, MixedExprTest)
{
  using namespace AST;
  AstPrinter printer;
  ExpressionPtr unary_right(new Literal(123ull));
  ExpressionPtr unary_expr(new Unary(unary_right, Token { Parse::TokenType::MINUS, "-", 1 }));
  ExpressionPtr grouping_literal(new Literal(45.67));
  ExpressionPtr grouping_expr(new Grouping(grouping_literal));
  auto expr = std::make_unique<Binary>(unary_expr, grouping_expr, Token { Parse::TokenType::STAR, "*", 1 });
  auto result = printer.toString(*expr);
  ASSERT_EQ(result, "(* (- 123) (group 45.670000))");
}
