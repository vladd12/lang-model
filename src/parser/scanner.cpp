#include "lang-model/parser/scanner.hpp"

#include <lang-model/tools/error_handler.hpp>

namespace Parse
{

Scanner::Scanner() : m_start(0), m_current(0), m_line(1)
{
}

void Scanner::reset(const std::string_view &source)
{
    m_source = source;
    m_start = 0;
    m_current = 0;
    m_line = 1;
    m_tokens.clear();
}

bool Scanner::isAtEnd() noexcept
{
    return m_current >= m_source.length();
}

char Scanner::advance()
{
    ++m_current;
    return m_source[m_current - 1];
}

bool Scanner::match(const char expected)
{
    if (isAtEnd())
        return false;
    if (m_source[m_current] != expected)
        return false;
    m_current++;
    return true;
}

char Scanner::peek()
{
    if (isAtEnd())
        return '\0';
    else
        return m_source[m_current];
}

char Scanner::peekNext()
{
    if (m_current + 1 >= m_source.length())
        return '\0';
    else
        return m_source[m_current + 1];
}

bool Scanner::isDigit(const char c)
{
    return ((c >= '0') && (c <= '9'));
}

bool Scanner::isAlpha(const char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(const char c)
{
    return isAlpha(c) || isDigit(c);
}

void Scanner::scan_string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            m_line++;
        advance();
    }
    if (!isAtEnd())
    {
        // The closing ".
        advance();
        // const auto value = m_source.substr(m_start + 1, m_current - 1);
        addToken(TokenType::STRING);
    }
    else
        tools::ErrorHandler::error(m_line, "Unterminated string!");
}

void Scanner::scan_number()
{
    while (isDigit(peek()))
        advance();
    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance();
        while (isDigit(peek()))
            advance();
    }
    // const auto value = m_source.substr(m_start, m_current);
    addToken(TokenType::NUMBER);
}

void Scanner::scan_identifier()
{
    while (isAlphaNumeric(peek()))
        advance();
    addToken(TokenType::IDENTIFIER);
}

void Scanner::addToken(const TokenType type)
{
    const auto text = m_source.substr(m_start, m_current);
    m_tokens.push_back(Token { type, text, m_line });
}

void Scanner::scanToken()
{
    char c = advance();
    switch (c)
    {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case '.':
        addToken(TokenType::DOT);
        break;
    case '-':
        addToken(TokenType::MINUS);
        break;
    case '+':
        addToken(TokenType::PLUS);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if (match('/'))
        {
            // A comment goes until the end of the line.
            while (peek() != '\n' && !isAtEnd())
                advance();
        }
        else
            addToken(TokenType::SLASH);
        break;
    case '"':
        scan_string();
        break;
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;
    case '\n':
        m_line++;
        break;
    default:
        if (isDigit(c))
            scan_number();
        else
            tools::ErrorHandler::error(m_line, "Unexpected character!");
        break;
    }
}

std::vector<Token> Scanner::scan(const std::string_view &source)
{
    reset(source);
    while (!isAtEnd())
    {
        m_start = m_current;
        scanToken();
    }
    m_tokens.push_back(Token { TokenType::EOF_, "", m_line });
    return m_tokens;
}

} // namespace Parse
