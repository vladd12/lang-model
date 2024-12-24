#include "lang-model/parser/token.hpp"

#include <magic_enum.hpp>

namespace Parse
{

Token::Token(const TokenType type, const std::string_view &lexeme, const std::uint64_t line)
    : m_type(type), m_lexeme(lexeme), m_line(line)
{
}

std::string Token::toString() const
{
    return std::string(magic_enum::enum_name(m_type)) + " " + std::string(m_lexeme);
}

Token::operator TokenType() const noexcept
{
    return m_type;
}

} // namespace Parse
