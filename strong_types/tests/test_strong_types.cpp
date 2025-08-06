/**
 * @file test_strong_types.cpp
 * @brief
 *
 * @author Philipp Jeske
 * @date 2025-08-06
 */

#include <pjexx/strong_types.h>

#include <catch2/catch_all.hpp>
#include <string>
#include <type_traits>

// Example strong_type implementation for testing
namespace pjexx::strong_types::test
{
using Width = strong_type<int, struct WidthTag>;
using Length = strong_type<int, struct LengthTag>;
using Name  = strong_type<std::string, struct NameTag>;

TEST_CASE("strong_type basic usage", "[strong_type]")
{
    Width m1 {5};
    Width m2 {10};
    Width m3 {5};
    Length m4 {15};
    Name n1 {"Alice"};
    Name n2 {"Bob"};

    SECTION("Construction and get")
    {
        REQUIRE(m1.get() == 5);
        REQUIRE(n1.get() == "Alice");
    }

    SECTION("Equality and inequality")
    {
        REQUIRE(m1 == m3);
        REQUIRE(m1 != m2);
        REQUIRE(n1 != n2);
    }

    SECTION("Type safety")
    {
        // The following lines should not compile if uncommented:
        // Width m = n1;
        // REQUIRE(m1 == m4);
        REQUIRE(std::is_constructible_v<Width, int>);
        REQUIRE_FALSE(std::is_constructible_v<Width, Name>);
    }

    SECTION("Ordering")
    {
        REQUIRE(m1 < m2);
        REQUIRE(m2 > m1);
        REQUIRE(m1 <= m3);
        REQUIRE(m1 >= m3);
        REQUIRE(m1 >= m1);
        REQUIRE(m1 <= m1);
    }

    SECTION("Casting to and from underlying type")
    {
        int raw = static_cast<int>(m1.get());
        REQUIRE(raw == 5);
        
        // The violation is part of the test, therefore ok
        // NOLINTNEXTLINE(cppcoreguidelines-init-variables,modernize-use-auto)
        Width w_from_int = static_cast<Width>(raw);
        REQUIRE(w_from_int == m1);

        // Implicit conversion should not be allowed:
        static_assert(!std::is_convertible_v<Width, int>, "Width should not be implicitly convertible to int");
        static_assert(!std::is_convertible_v<int, Width>, "int should not be implicitly convertible to Width");
    }
}
}  // namespace pjexx::strong_types::test
