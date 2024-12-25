#include "lang-model/utils/interpreter.hpp"

#include <iostream>
#include <lang-model/parser/file_reader.hpp>

namespace Utils
{

Interpreter::Interpreter(const CommandLineArguments &args) : desc { "Interpreter options: " }
{
  desc.add_options()                                                //
    ("file,-F", opt::value<std::string>(), "File with source code") //
    ("help,-H", "Show help message");                               //
  opt::store(opt::parse_command_line(args.argc, args.argv, desc), vars, /* utf8 = */ true);
  opt::notify(vars);
}

void Interpreter::runLine(const std::string_view &line)
{
  std::cout << "Debug output: " << line << '\n';
  // TODO: really run line
  return;
}

void Interpreter::runPromt()
{
  std::string line;
  std::cout << "> ";
  while (std::getline(std::cin, line))
  {
    if (!line.empty())
    {
      if (line == "exit")
        break;
      else
      {
        runLine(line);
        std::cout << "> ";
      }
    }
  }
}

void Interpreter::runFile(const std::string &filepath)
{
  // Debug purposes
  std::cout << filepath << '\n';
  try
  {
    Parse::FileReader fileReader;
    fileReader.readFile(filepath);
    runLine(fileReader.getBuffer());
  } catch (const std::exception &ex)
  {
    std::cout << ex.what();
  }
}

void Interpreter::run()
{
  if (vars.count("file")) // run file in interpreter
  {
    Parse::FileReader fileReader;
    std::string filepath(vars["file"].as<std::string>());
    runFile(filepath);
  }
  else if (vars.count("help")) // show help message
    std::cout << desc << "\n";
  else // run promt
    runPromt();
}

} // namespace tools
