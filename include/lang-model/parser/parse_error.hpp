#pragma once

#include <lang-model/export.hpp>
#include <stdexcept>

namespace Parse
{

class libapi ParseError final : public std::runtime_error
{
public:
  explicit ParseError(const std::string &message);
  explicit ParseError(const char *message);
};

} // namespace Parse
