/**
 * @file concepts.h
 * @brief
 *
 * @author Philipp Jeske
 * @date 2025-08-06
 */

#pragma once
#ifndef PJEXX_STRONG_TYPES_CONCEPTS_H
#define PJEXX_STRONG_TYPES_CONCEPTS_H

#include <concepts>

namespace pjexx::strong_types::concepts
{

template <class T>
concept is_addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template <class T>
concept is_multiplyable = requires(T a, T b) {
    { a * b } -> std::same_as<T>;
};

template <class T>
concept is_subtractable = requires(T a, T b) {
    { a - b } -> std::same_as<T>;
};

template <class T>
concept is_divideable = requires(T a, T b) {
    { a / b } -> std::same_as<T>;
};

}  // namespace pjexx::strong_types::concepts

#endif  // PJEXX_STRONG_TYPES_CONCEPTS_H
