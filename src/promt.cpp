#include <iostream>
#include <lang-model/promt.hpp>

namespace tools
{

void Promt::runLine(const std::string_view &line) noexcept
{
    std::cout << "Debug output: " << line << '\n';
    // TODO: really run line
    return;
}

void Promt::run() noexcept
{
    std::string line;
    std::cout << "> ";
    while (std::getline(std::cin, line))
    {
        runLine(line);
        std::cout << "> ";
    }
}

} // namespace tools
