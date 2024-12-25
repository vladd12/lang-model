#pragma once

#include <boost/program_options.hpp>
#include <lang-model/export.hpp>
#include <string>

namespace Utils
{

namespace opt = boost::program_options;

struct CommandLineArguments
{
  int argc;
  char **argv;
};

class libapi Interpreter final
{
private:
  opt::options_description desc;
  opt::variables_map vars;

  void runLine(const std::string_view &line);
  void runPromt();
  void runFile(const std::string &filepath);

public:
  Interpreter() = delete;
  Interpreter(const CommandLineArguments &args);
  ~Interpreter() = default;

  void run();
};

} // namespace tools
