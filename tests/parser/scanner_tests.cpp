#include <gtest/gtest.h>
#include <lang-model/parser/scanner.hpp>

TEST(Scanner, ScannerTest_01)
{
    Parse::Scanner scanner;
    auto result = scanner.scan(R"(
    var a = 1.1
    )");
    ASSERT_TRUE(result.size() > 0);
}
