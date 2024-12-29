#pragma once

#include <lang-model/ast/expression.hpp>
#include <string>
#include <variant>

namespace AST
{

struct nil_value
{
};

class libapi Literal final : public Expression
{
public:
  using holder_type = std::variant<std::uint64_t, std::int64_t, double, bool, char, std::string, nil_value>;

private:
  holder_type m_value;

public:
  explicit Literal() noexcept;

  Literal(const std::uint64_t value) noexcept;
  Literal(const std::int64_t value) noexcept;
  Literal(const double value) noexcept;
  explicit Literal(const std::string &value);
  explicit Literal(const char value) noexcept;
  explicit Literal(const bool value) noexcept;

  holder_type &get() noexcept;
  const holder_type &get() const noexcept;

  void accept(Visitor &visitor) override;
};

} // namespace AST
