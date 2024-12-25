#include <fstream>
#include <lang-model/parser/file_reader.hpp>
#include <sstream>

namespace Parse
{

FileReader::FileReader(const std::string &filepath)
{
  readFile(filepath);
}

void FileReader::readFile(const std::string &filepath)
{
  std::ifstream file(filepath);
  file.exceptions(std::ios_base::badbit);
  /// TODO: Replace by errorFlag
  if (!file)
  {
    throw std::ios_base::failure("file does not exist");
  }
  std::ostringstream stringStream;
  stringStream << file.rdbuf();
  fileString = stringStream.str();
  fileView = fileString;
}

const std::string_view &FileReader::getBuffer() const noexcept
{
  return fileView;
}

} // namespace Parse
