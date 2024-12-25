#include "lang-model/parser/scanner.hpp"

#include <lang-model/utils/error_handler.hpp>

namespace Parse
{

const std::unordered_map<std::string_view, TokenType> Scanner::s_keywords {
  { "if", TokenType::IF },         //
  { "else", TokenType::ELSE },     //
  { "true", TokenType::TRUE },     //
  { "false", TokenType::FALSE },   //
  { "and", TokenType::AND },       //
  { "or", TokenType::OR },         //
  { "for", TokenType::FOR },       //
  { "while", TokenType::WHILE },   //
  { "var", TokenType::VAR },       //
  { "nil", TokenType::NIL },       //
  { "print", TokenType::PRINT },   //
  { "return", TokenType::RETURN }, //
  { "fun", TokenType::FUN },       //
  { "class", TokenType::CLASS },   //
  { "this", TokenType::THIS },     //
  { "super", TokenType::SUPER },   //
};

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
  return m_source[m_current++];
}

bool Scanner::match(const char expected)
{
  if (isAtEnd())
    return false;
  if (m_source[m_current] != expected)
    return false;
  ++m_current;
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

std::string_view Scanner::get_current_lexeme()
{
  return m_source.substr(m_start, m_current - m_start);
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
    addToken(TokenType::STRING);
  }
  else
    Utils::ErrorHandler::error(m_line, "Unterminated string!");
}

void Scanner::scan_number()
{
  while (isDigit(peek()))
    advance();
  TokenType type = TokenType::INTEGER;
  // Look for a fractional part.
  if (peek() == '.' && isDigit(peekNext()))
  {
    type = TokenType::FLOAT;
    advance();
    while (isDigit(peek()))
      advance();
  }
  addToken(type);
}

void Scanner::scan_identifier()
{
  while (isAlphaNumeric(peek()))
    advance();
  TokenType type = TokenType::IDENTIFIER;
  auto search = s_keywords.find(get_current_lexeme());
  if (search != s_keywords.cend())
    type = search->second;
  addToken(type);
}

void Scanner::addToken(const TokenType type)
{
  m_tokens.push_back(Token { type, get_current_lexeme(), m_line });
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
    else if (match('*'))
    {
      // Multy-line comment.
      while (!isAtEnd())
      {
        if (peek() == '*' && peekNext() == '/')
          break;
        advance();
      }
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
    else if (isAlpha(c))
      scan_identifier();
    else
      Utils::ErrorHandler::error(m_line, "Unexpected character!");
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
