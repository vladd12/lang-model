#include "lang-model/tools/error_handler.hpp"

#include <iostream>

namespace tools
{

void ErrorHandler::error(unsigned int line, const std::string_view &message)
{
    report(line, "", message);
}

void ErrorHandler::report(unsigned int line, const std::string_view &where, const std::string_view &message)
{
    std::cerr << "[line " << line << "] Error " << where << ": " << message;
}

} // namespace tools
