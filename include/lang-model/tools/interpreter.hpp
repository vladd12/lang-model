#pragma once

#include <boost/program_options.hpp>
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

public:
    Interpreter() = delete;
    Interpreter(const CommandLineArguments &args);
    ~Interpreter() = default;

    void run(std::istream &inputStream = std::cin) noexcept;
    void start() noexcept;
};

} // namespace tools
