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

TEST(AstPrinter, MixedLiteralsTest)
{
  using namespace AST;
  AstPrinter printer;
  ExpressionPtr unsigned_value(new Literal(123ull));
  auto result = printer.toString(*unsigned_value);
  ASSERT_EQ(result, "123");
  ExpressionPtr signed_value(new Literal(-456ll));
  result = printer.toString(*signed_value);
  ASSERT_EQ(result, "-456");
  ExpressionPtr float_value(new Literal(1.1f));
  result = printer.toString(*float_value);
  ASSERT_EQ(result, "1.100000");
  ExpressionPtr double_value(new Literal(3.0));
  result = printer.toString(*double_value);
  ASSERT_EQ(result, "3.000000");
  ExpressionPtr char_value(new Literal('a'));
  result = printer.toString(*char_value);
  ASSERT_EQ(result, "'a'");
  ExpressionPtr true_value(new Literal(true));
  result = printer.toString(*true_value);
  ASSERT_EQ(result, "true");
  ExpressionPtr false_value(new Literal(false));
  result = printer.toString(*false_value);
  ASSERT_EQ(result, "false");
  /// TODO: well, here we are calling bool ctor... Fix me?
  ExpressionPtr str_value(new Literal("this is string"));
  result = printer.toString(*str_value);
  // ASSERT_EQ(result, "'this is string'");
  ExpressionPtr nil_value(new Literal);
  result = printer.toString(*nil_value);
  ASSERT_EQ(result, "nil");
}
