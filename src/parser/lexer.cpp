#include <array>
#include <lang-model/parser/lexer.hpp>

/*
 * "var a = 1;"
 * "var b=1+2;\n\r var c = b;"
 */

namespace Parse
{

// Lexer::Lexer(const FileReader &reader, const size_t prealloc) noexcept
//{
//    tokens.reserve(prealloc);
//    scanTokens(reader.getBuffer());
//}

Lexer::Lexer(const std::string_view &source, const std::size_t prealloc) noexcept
{
    tokens.reserve(prealloc);
    scanTokens(source);
}

void Lexer::scanTokens(const std::string_view &source) noexcept
{
    using namespace std::string_view_literals;
    firstScan(tokens, source, " \n\r\t"sv);
}

void Lexer::firstScan(std::vector<std::string_view> &tokens, //
    const std::string_view &source, const std::string_view &pattern) noexcept
{
    auto patternIndex = source.find_first_of(pattern);
    if (patternIndex != std::string_view::npos)
    {
        auto token = source.substr(0, patternIndex);
        if (token.size() > 0)
            tokens.push_back(token);
        firstScan(tokens, source.substr(patternIndex + 1), pattern);
    }
    else
    {
        if (source.size() > 0)
            tokens.push_back(source);
    }
}

const std::vector<std::string_view> &Lexer::getTokens() const noexcept
{
    return tokens;
}

} // namespace Parse
