#include <gtest/gtest.h>
#include <lang-model/ast/visit/ast_printer.hpp>
#include <lang-model/parser/grammar_parser.hpp>
#include <lang-model/parser/scanner.hpp>

namespace
{

inline std::string mixing_logic(const std::string_view &raw_text)
{
  using namespace ::Parse;
  using namespace ::AST;
  Scanner scanner;
  AstPrinter printer;
  auto tokens { scanner.scan(raw_text) };
  GrammarParser parser { tokens };
  bool ok = true;
  auto ast = parser.parse(&ok);
  if (ok && ast)
    return printer.toString(*ast);
  else
    return "";
}

}

TEST(GrammarParser, SimpleTest)
{
  auto result = ::mixing_logic(R"(
    1+1.1/22
  )");
  EXPECT_EQ(result, "(+ 1 (/ 1.100000 22))");
  result = ::mixing_logic(R"(
    (2+1)/35
  )");
  EXPECT_EQ(result, "(/ (group (+ 2 1)) 35)");
}
