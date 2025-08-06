/**
 * @file strong_types.h
 * @brief Strong typedef wrapper for type-safe programming.
 *
 * @author Philipp Jeske
 * @date 2025-08-06
 */
// SPDX-License-Identifier: MIT

#pragma once
#ifndef PJEXX_STRONG_TYPES_H
#define PJEXX_STRONG_TYPES_H

#include <compare>
#include <concepts>
#include <typeindex>

#include "strong_types/concepts.h"

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

    template <concepts::is_addable U = T>
    constexpr self_type& operator+=(const strong_type<U, Tag>& rhs)
    {
        value_ += rhs.value_;
        return *this;
    }

    template <concepts::is_subtractable U = T>
    constexpr self_type& operator-=(const strong_type<U, Tag>& rhs)
    {
        value_ -= rhs.value_;
        return *this;
    }

    template <concepts::is_multiplyable U = T>
    constexpr self_type& operator*=(const strong_type<U, Tag>& rhs)
    {
        value_ *= rhs.value_;
        return *this;
    }

    template <concepts::is_divideable U = T>
    constexpr self_type& operator/=(const strong_type<U, Tag>& rhs)
    {
        value_ /= rhs.value_;
        return *this;
    }

    template <concepts::is_addable U>
    friend constexpr strong_type<U, Tag> operator+(const strong_type<U, Tag>& lhs, const strong_type<U, Tag>& rhs)
    {
        return strong_type<U, Tag>(lhs.value_ + rhs.value_);
    }

    template <concepts::is_divideable U>
    friend constexpr strong_type<U, Tag> operator/(const strong_type<U, Tag>& lhs, const strong_type<U, Tag>& rhs)
    {
        return strong_type<U, Tag>(lhs.value_ / rhs.value_);
    }

    template <concepts::is_multiplyable U>
    friend constexpr strong_type<U, Tag> operator*(const strong_type<U, Tag>& lhs, const strong_type<U, Tag>& rhs)
    {
        return strong_type<U, Tag>(lhs.value_ * rhs.value_);
    }

    template <concepts::is_subtractable U>
    friend constexpr strong_type<U, Tag> operator-(const strong_type<U, Tag>& lhs, const strong_type<U, Tag>& rhs)
    {
        return strong_type<U, Tag>(lhs.value_ - rhs.value_);
    }

    template <std::equality_comparable U>
    friend constexpr bool operator==(const strong_type<U, Tag>& lhs, const strong_type<U, Tag>& rhs)
    {
        return lhs.value_ == rhs.value_;
    }

    template <std::three_way_comparable U>
    friend constexpr auto operator<=>(const strong_type<U, Tag>& lhs, const strong_type<U, Tag>& rhs)
    {
        return lhs.value_ <=> rhs.value_;
    }

  private:
    T value_;
};

}  // namespace pjexx::strong_types

namespace std
{
template <typename T, typename Tag>
struct hash<pjexx::strong_types::strong_type<T, Tag>>
{
    size_t operator()(const pjexx::strong_types::strong_type<T, Tag>& st) const { return std::hash<T>()(st.get()); }
};
}  // namespace std

#endif  // PJEXX_STRONG_TYPES_H
