#include "lang-model/tools/interpreter.hpp"

#include <lang-model/parser/file_reader.hpp>

namespace tools
{

Interpreter::Interpreter(const CommandLineArguments &args) : desc { "Interpreter options: " }
{
    desc.add_options()                                                  //
        ("file,-F", opt::value<std::string>(), "File with source code") //
        ("help,-H", "Show help message");                               //
    opt::store(opt::parse_command_line(args.argc, args.argv, desc), vars, /* utf8 = */ true);
    opt::notify(vars);
}

void Interpreter::runLine(const std::string_view &line) noexcept
{
    std::cout << "Debug output: " << line << '\n';
    // TODO: really run line
    return;
}

void Interpreter::runPromt(std::istream &inputStream) noexcept
{
    std::string line;
    std::cout << "> ";
    while (std::getline(inputStream, line))
    {
        if (!line.empty() && line != "exit")
        {
            runLine(line);
            std::cout << "> ";
        }
        else
            break;
    }
}

void Interpreter::runFile(const std::ifstream &inputFile) noexcept
{
    ;
}

void Interpreter::run() noexcept
{
    static Parse::FileReader fileReader;
    // show help message
    if (vars.count("help"))
    {
        std::cout << desc << "\n";
    }
    // run file in interpreter
    else if (vars.count("file"))
    {
        std::string filepath(vars["file"].as<std::string>());
        // Debug purposes
        std::cout << filepath << '\n';
        fileReader.readFile(filepath);
        // TODO: execute interpreter with selected file
    }
    // run promt
    else
    {
        runPromt(std::cin);
    }
}

} // namespace tools
