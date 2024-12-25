#include <gtest/gtest.h>
#include <lang-model/parser/file_reader.hpp>

TEST(FileReader, ReadFileTest)
{
  Parse::FileReader reader("read_file_test.meta");
  constexpr std::string_view expected("\nlet a = 1 + 1;\nvar b = a;\nlet c = a / b;\n");
  auto &actual = reader.getBuffer();
  ASSERT_EQ(expected, actual);
}
