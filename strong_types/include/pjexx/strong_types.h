/**
 * @file strong-types.h
 * @brief
 *
 * @author Philipp Jeske
 * @date 2025-08-06
 */

#pragma once
#ifndef PJEXX_STRONG_TYPES_H
#define PJEXX_STRONG_TYPES_H

namespace pjexx::strong_types
{

template <typename T, typename Tag>
class strong_type
{
  public:
    using self_type  = strong_type<T, Tag>;
    using value_type = T;

    explicit constexpr strong_type(T value) : value_(value) {}

    constexpr T get() const { return value_; }
    explicit constexpr operator T() const { return value_; }

    friend constexpr self_type operator+(const self_type& lhs, const self_type& rhs)
    {
        return self_type(lhs.value_ + rhs.value_);
    }

    friend constexpr bool operator==(const self_type& lhs, const self_type& rhs) { return lhs.value_ == rhs.value_; }

    friend constexpr auto operator<=>(const self_type& lhs, const self_type& rhs) { return lhs.value_ <=> rhs.value_; }

  private:
    T value_;
};

}  // namespace pjexx::strong_types

#endif  // PJEXX_STRONG_TYPES_H
