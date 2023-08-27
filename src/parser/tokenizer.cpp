#include <array>
#include <lang-model/parser/tokenizer.hpp>

/*
 * "var a = 1;"
 * "var b=1+2;\n\r var c = b;"
 */

namespace Parse
{

constexpr std::string_view::size_type start = 0;
constexpr auto notFound = std::string_view::npos;

Tokenizer::Tokenizer(const std::string_view &src, const std::size_t prealloc) noexcept : source(src)
{
    tokens.reserve(prealloc);
    scanTokens();
}

void Tokenizer::addToken(const std::string_view &token) noexcept
{
    if (token.size() > 0)
        tokens.push_back(token);
}

void Tokenizer::scanSpecialSymbols(std::string_view &possibleToken) noexcept
{
    using namespace std::string_view_literals;
    constexpr std::string_view special_sym("=([{+-/*^><@}]);"sv);
    auto searchIndex = notFound;

    do
    {
        searchIndex = possibleToken.find_first_of(special_sym);
        if (searchIndex != notFound)
        {
            // TODO: What about '[[', ']]', '<<', '>>' and '**'? Think about it later.
            auto firstToken = possibleToken.substr(0, searchIndex);
            auto secondToken = possibleToken.substr(searchIndex, 1);
            addToken(firstToken);
            addToken(secondToken);

            // Обработка конца строки
            if ((searchIndex + 1) == possibleToken.size())
                searchIndex = notFound;
            else
                possibleToken = possibleToken.substr(searchIndex + 1);
        }
        else
        {
            addToken(possibleToken);
        }
    } while (searchIndex != notFound && possibleToken.size() > 0);
}

void Tokenizer::scanTokens() noexcept
{
    using namespace std::string_view_literals;
    constexpr std::string_view delimeters(" \n\r\t"sv);

    auto searchIndex = notFound;
    std::string_view possibleToken;

    do
    {
        searchIndex = source.find_first_of(delimeters); // ищем delimeters
        // получаем возможный токен
        if (searchIndex != notFound)
            possibleToken = source.substr(0, searchIndex);
        else
            possibleToken = source;
        // дополнительно обрабатываем возможный токен
        if (possibleToken.size() > 0)
            scanSpecialSymbols(possibleToken);
        // обрезаем исходную строку
        if (searchIndex != notFound)
            source = source.substr(searchIndex + 1);
    } while (searchIndex != notFound && source.size() > 0);
}

void Tokenizer::update(const std::string_view &newSource) noexcept
{
    source = newSource;
    tokens.clear();
    scanTokens();
}

const std::vector<std::string_view> &Tokenizer::getTokens() const noexcept
{
    return tokens;
}

} // namespace Parse
