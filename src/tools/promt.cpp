#include <lang-model/tools/promt.hpp>

namespace tools
{

void Promt::runLine(const std::string_view &line) noexcept
{
    std::cout << "Debug output: " << line << '\n';
    // TODO: really run line
    return;
}

void Promt::run(std::istream &inputStream) noexcept
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

} // namespace tools
