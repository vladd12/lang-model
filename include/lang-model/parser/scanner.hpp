#pragma once

#include <lang-model/parser/token.hpp>
#include <unordered_map>
#include <vector>

namespace Parse
{

class libapi Scanner final
{
private:
  static const std::unordered_map<std::string_view, TokenType> s_keywords;

  std::string_view m_source;
  std::vector<Token> m_tokens;
  std::size_t m_start, m_current, m_line;

  void reset(const std::string_view &source);
  bool isAtEnd() noexcept;
  char advance();
  bool match(const char expected);
  char peek();
  char peekNext();
  std::string_view get_current_lexeme();

  bool isDigit(const char c);
  bool isAlpha(const char c);
  bool isAlphaNumeric(const char c);

  void scan_string();
  void scan_number();
  void scan_identifier();

  void addToken(const TokenType type);
  void scanToken();

public:
  explicit Scanner();
  std::vector<Token> scan(const std::string_view &source);
};

} // namespace Parse
