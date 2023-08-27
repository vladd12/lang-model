#pragma once

#include <lang-model/parser/file_reader.hpp>

namespace Parse
{

class libapi Tokenizer
{
private:
    std::string_view source;
    std::vector<std::string_view> tokens;

    void addToken(const std::string_view &token) noexcept;
    void scanSpecialSymbols(std::string_view &possibleToken) noexcept;
    void scanTokens() noexcept;

public:
    Tokenizer() = delete;
    explicit Tokenizer(const std::string_view &src, const std::size_t prealloc = 512) noexcept;

    void update(const std::string_view &newSource) noexcept;
    const std::vector<std::string_view> &getTokens() const noexcept;
};

} // namespace Parse
