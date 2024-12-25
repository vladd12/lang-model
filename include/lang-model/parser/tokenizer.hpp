#pragma once

#include <lang-model/parser/file_reader.hpp>

namespace Parse
{

class libapi Tokenizer
{
private:
  std::string_view source;
  std::vector<std::string_view> tokens;

  /// \brief Добавляет token в список токенов, если это не пустая строка.
  void addToken(const std::string_view &token) noexcept;
  /// \brief Функция для обработки пробелов или их отсутсвия между спец. символами.
  /// \details Учтённые спец. символы на данный момент: =([{+-/*^><@}]);
  void scanSpecialSymbols(std::string_view &possibleToken) noexcept;
  /// \brief Функция для парсинга строки source и разделения её на токены.
  void scanTokens() noexcept;

public:
  Tokenizer() = delete;
  explicit Tokenizer(const std::string_view &src, const std::size_t prealloc = 512) noexcept;

  /// \brief Возвращает ссылку на список токенов, хранимых в результате парсинга.
  const std::vector<std::string_view> &getTokens() const noexcept;
  /// \brief Обновляет список токенов новой строкой с исходным кодом.
  void update(const std::string_view &newSource) noexcept;
};

} // namespace Parse
