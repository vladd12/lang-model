#pragma once

#include <lang-model/ast/expression.hpp>
#include <string>
#include <variant>

namespace AST
{

class Literal final : public Expression
{
public:
  using holder_type = std::variant<std::uint64_t, std::int64_t, double, bool, char, std::string>;

private:
  holder_type m_value;

public:
  explicit Literal() = delete;

  Literal(const std::uint64_t value) noexcept;
  Literal(const std::int64_t value) noexcept;
  Literal(const double value) noexcept;
  Literal(const bool value) noexcept;
  Literal(const char value) noexcept;
  Literal(const std::string &value);

  holder_type &get() noexcept;
  const holder_type &get() const noexcept;

  void accept(Visitor &visitor) override;
};

} // namespace AST
