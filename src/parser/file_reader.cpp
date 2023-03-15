#include <fstream>
#include <lang-model/parser/file_reader.hpp>
#include <sstream>

namespace Parse
{

void FileReader::readFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::ostringstream stringStream;
    stringStream << file.rdbuf();
    auto fileString = stringStream.str();
    splitFileToBuffer(fileString);
}

void FileReader::splitFileToBuffer(const std::string &fileStr)
{
    ;
}

} // namespace Parse

std::string::difference_type n = std::count(s.begin(), s.end(), '_');
