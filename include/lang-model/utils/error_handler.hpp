#pragma once

#include <lang-model/export.hpp>
#include <string_view>

namespace Parse
{
class Token;
} // namespace Parse

namespace Utils
{

class libapi ErrorHandler final
{
public:
  ErrorHandler() = delete;
  ~ErrorHandler() = delete;

  static void error(unsigned int line, const std::string_view &message);
  static void error(const ::Parse::Token &token, const std::string_view &message);
  static void report(unsigned int line, const std::string_view &where, const std::string_view &message);
};

} // namespace tools
