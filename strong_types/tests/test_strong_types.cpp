/**
 * @file test_strong_types.cpp
 *
 * @author Philipp Jeske
 * @date 2025-08-06
 */
// SPDX-License-Identifier: MIT

#include <pjexx/strong_types.h>

#include <catch2/catch_all.hpp>
#include <string>
#include <type_traits>
#include <unordered_set>

namespace pjexx::strong_types::test
{
// NOLINTBEGIN(readability-identifier-length,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
using Width  = strong_type<int, struct WidthTag>;
using Length = strong_type<int, struct LengthTag>;
using Name   = strong_type<std::string, struct NameTag>;

TEST_CASE("strong_type basic usage", "[strong_type][basic usage]")
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

TEST_CASE("strong_type arithmetic operations", "[strong_type][arithmetic]")
{
    Width w1 {3};
    Width w2 {7};
    Length l1 {2};
    Length l2 {5};
    Name n1 {"Alice"};
    Name n2 {"Bob"};

    SECTION("Addition and subtraction for arithmetic types")
    {
        auto w_sum  = w1 + w2;
        auto w_diff = w2 - w1;
        REQUIRE(w_sum.get() == 10);
        REQUIRE(w_diff.get() == 4);

        auto l_sum  = l1 + l2;
        auto l_diff = l2 - l1;
        REQUIRE(l_sum.get() == 7);
        REQUIRE(l_diff.get() == 3);
    }

    SECTION("Compound assignment for arithmetic types")
    {
        Width w = w1;
        w += w2;
        REQUIRE(w.get() == 10);
        w -= w1;
        REQUIRE(w.get() == 7);
    }

    SECTION("Multiplication and division for arithmetic types")
    {
        auto w_mul = w1 * w2;
        auto w_div = w2 / w1;
        REQUIRE(w_mul.get() == 21);
        REQUIRE(w_div.get() == 2);
    }
}

TEST_CASE("strong_type hash functionality", "[strong_type][hash]")
{
    Width w1 {42};
    Width w2 {42};
    Width w3 {7};
    Name n1 {"Alice"};
    Name n2 {"Bob"};

    // Test std::hash for equality
    std::hash<Width> width_hasher;
    REQUIRE(width_hasher(w1) == width_hasher(w2));
    REQUIRE(width_hasher(w1) != width_hasher(w3));

    std::hash<Name> name_hasher;
    REQUIRE(name_hasher(n1) != name_hasher(n2));

    // Test usage in unordered containers
    std::unordered_map<Width, std::string> width_map;
    width_map[w1] = "forty-two";
    REQUIRE(width_map[w2] == "forty-two");

    std::unordered_set<Name> name_set;
    name_set.insert(n1);
    REQUIRE(name_set.contains(n1));
    REQUIRE_FALSE(name_set.contains(n2));
}

TEST_CASE("strong_type stream operators", "[strong_type][stream]")
{
    Width w {123};
    Length l {456};
    Name n {"Charlie"};

    SECTION("Output stream operator")
    {
        std::ostringstream oss;
        oss << w;
        REQUIRE(oss.str() == "123");

        std::ostringstream oss2;
        oss2 << l;
        REQUIRE(oss2.str() == "456");

        std::ostringstream oss3;
        oss3 << n;
        REQUIRE(oss3.str() == "Charlie");
    }

    SECTION("Input stream operator")
    {
        std::istringstream iss("789");
        Width w2 {0};
        iss >> w2;
        REQUIRE(w2.get() == 789);

        std::istringstream iss2("999");
        Length l2 {0};
        iss2 >> l2;
        REQUIRE(l2.get() == 999);

        std::istringstream iss3("Delta");
        Name n2 {""};
        iss3 >> n2;
        REQUIRE(n2.get() == "Delta");
    }
}

#if defined(__cpp_lib_format) || __has_include(<fmt/format.h>)
TEST_CASE("strong_type format support", "[strong_type][format]")
{
#ifdef __cpp_lib_format
    using std::format;
#else
    using fmt::format;
#endif

    Width w {42};
    Length l {99};
    Name n {"Eve"};

    SECTION("Format with std::format")
    {
        REQUIRE(format("Width: {}", w) == "Width: 42");
        REQUIRE(format("Length: {}", l) == "Length: 99");
        REQUIRE(format("Name: {}", n) == "Name: Eve");
    }
}
#endif
// NOLINTEND(readability-identifier-length,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
}  // namespace pjexx::strong_types::test
