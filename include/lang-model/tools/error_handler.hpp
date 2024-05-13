#pragma once

#include <lang-model/export.hpp>
#include <string_view>

namespace tools
{

class libapi ErrorHandler final
{
public:
    ErrorHandler() = delete;
    ~ErrorHandler() = delete;

    static void error(unsigned int line, const std::string_view &message);
    static void report(unsigned int line, const std::string_view &where, const std::string_view &message);
};

} // namespace tools
