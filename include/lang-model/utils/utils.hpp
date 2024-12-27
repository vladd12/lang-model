#pragma once

namespace Utils
{

// helper type for the visitor
template <class... Ts> //
struct overloaded : Ts...
{
  using Ts::operator()...;
};

// explicit deduction guide
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

} // namespace Utils
