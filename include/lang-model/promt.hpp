#pragma once

#include <lang-model/export.hpp>
#include <string>

namespace tools
{

class libapi Promt final
{
private:
    void runLine(const std::string_view &line) noexcept;

public:
    Promt() = default;
    ~Promt() = default;

    void run() noexcept;
};

} // namespace tools
