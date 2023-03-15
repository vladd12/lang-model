#pragma once

#include <lang-model/export.hpp>
#include <string>
#include <vector>

namespace Parse
{

using StringList = std::vector<std::string>;

class libapi FileReader
{
private:
    StringList buffer;

    auto count();
    void splitFileToBuffer(const std::string &fileStr);

public:
    FileReader() = default;
    void readFile(const std::string &filepath);
};

} // namespace Parse
