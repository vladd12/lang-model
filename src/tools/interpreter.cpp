#include <lang-model/tools/interpreter.hpp>

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

void Interpreter::run(std::istream &inputStream) noexcept
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

void Interpreter::start() noexcept
{
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
        // TODO: execute interpreter with selected file
    }
    // run promt
    else
    {
        // tools::Interpreter promt;
        // promt.run();
        // TODO: execute interpreter promt
    }
}

} // namespace tools
