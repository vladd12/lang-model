#pragma once

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <lang-model/export.hpp>
#include <string>

namespace tools
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

    void runLine(const std::string_view &line) noexcept;
    void runPromt(std::istream &inputStream = std::cin) noexcept;
    void runFile(const std::ifstream &inputFile) noexcept;

public:
    Interpreter() = delete;
    explicit Interpreter(const CommandLineArguments &args);
    ~Interpreter() = default;

    void run() noexcept;
};

} // namespace tools
