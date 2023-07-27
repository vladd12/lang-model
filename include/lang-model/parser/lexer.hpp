#pragma once

#include <lang-model/parser/file_reader.hpp>

namespace Parse
{

class libapi Lexer
{
private:
    std::vector<std::string_view> tokens;

    void scanTokens(const std::string_view &source) noexcept;
    void firstScan(std::vector<std::string_view> &tokens, //
        const std::string_view &source, const std::string_view &pattern) noexcept;

public:
    Lexer() = delete;
    // explicit Lexer(const FileReader &reader, const std::size_t prealloc = 512) noexcept;
    explicit Lexer(const std::string_view &source, const std::size_t prealloc = 512) noexcept;

    const std::vector<std::string_view> &getTokens() const noexcept;
};

} // namespace Parse
