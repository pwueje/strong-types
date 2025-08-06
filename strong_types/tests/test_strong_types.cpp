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
}
}  // namespace pjexx::strong_types::test
