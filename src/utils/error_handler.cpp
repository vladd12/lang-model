#include "lang-model/utils/error_handler.hpp"

#include <fmt/core.h>
#include <iostream>
#include <lang-model/parser/token.hpp>

namespace Utils
{

void ErrorHandler::error(unsigned int line, const std::string_view &message)
{
  report(line, "", message);
}

void ErrorHandler::error(const ::Parse::Token &token, const std::string_view &message)
{
  if (::Parse::TokenType(token) == ::Parse::TokenType::EOF_)
    report(token.line(), " at end", message);
  else
    report(token.line(), fmt::format(" at '{0}'", token.lexeme()), message);
}

void ErrorHandler::report(unsigned int line, const std::string_view &where, const std::string_view &message)
{
  std::cerr << fmt::format("[Line {0}] Error {1}: {2}\n", line, where, message);
}

} // namespace tools
