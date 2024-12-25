#pragma once

#include <lang-model/export.hpp>
#include <string>
#include <vector>

namespace Parse
{

class libapi FileReader
{
private:
  std::string fileString;
  std::string_view fileView;

public:
  explicit FileReader() = default;
  explicit FileReader(const std::string &filepath);
  void readFile(const std::string &filepath);

  const std::string_view &getBuffer() const noexcept;
};

} // namespace Parse
