#pragma once

#include <cstdint>
#include <string>

namespace Parse
{

enum class TokenType : std::uint16_t
{
    // Single-character tokens.
    LEFT_PAREN = 0,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,
    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,
    EOF_ = UINT16_MAX
};

class Token final
{
private:
    TokenType m_type;
    std::string_view m_lexeme;
    std::uint64_t m_line;

public:
    explicit Token(const TokenType type, const std::string_view &lexeme, const std::uint64_t line);
    std::string toString();
};

} // namespace Parse
