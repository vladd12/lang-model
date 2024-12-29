#include "lang-model/parser/parse_error.hpp"

namespace Parse
{

ParseError::ParseError(const std::string &message) : std::runtime_error(message.c_str())
{
}

ParseError::ParseError(const char *message) : std::runtime_error(message)
{
}

} // namespace Parse
