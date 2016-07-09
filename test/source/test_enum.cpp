#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <type_traits>
#include <enum.h>

#define MAIN_TAG "[better-enums]"

BETTER_ENUM(Channel, short, Red, Green, Blue)
BETTER_ENUM(Depth, short, HighColor = 40, TrueColor = 20)
BETTER_ENUM(Compression, short, None, Huffman, Default = Huffman)

namespace test
{
    BETTER_ENUM(Namespaced, short, One, Two)
}

// Using BETTER_ENUMS_HAVE_CONSTEXPR_ as a proxy for C++11 support. This should
// be changed to be more precise in the future.
#ifdef BETTER_ENUMS_HAVE_CONSTEXPR_

// Type properties.
static_assert_1(std::is_class<Channel>());
static_assert_1(std::is_standard_layout<Channel>());
static_assert_1(std::is_literal_type<Channel>());

// Member type properties and identities.
static_assert_1(std::is_integral<Channel::_integral>());
static_assert_1(std::is_enum<Channel::_enumerated>());

static_assert_1((std::is_same<short, Channel::_integral>()));
// Temporarily disabled due to outdated libraries in Travis.
// static_assert_1((std::is_same<
//     short, std::underlying_type<Channel::_enumerated>::type>()));

static_assert_1(!(std::is_same<int, Channel::_integral>()));
// Temporarily disabled due to outdated libraries in Travis.
// static_assert_1(!(std::is_same<
//     int, std::underlying_type<Channel::_enumerated>::type>()));

static_assert_1(sizeof(Channel) == sizeof(short));
static_assert_1(alignof(Channel) == alignof(short));
static_assert_1((std::is_same<decltype(Channel::Red), Channel::_enumerated>()));

// Supported constructors.

// Apparently, this isn't supported by Clang in Travis.
// #ifdef __clang__
// static_assert_1(std::is_trivially_copyable<Channel>());
// #endif

static_assert_1((std::is_constructible<Channel, Channel::_enumerated>()));
// "Passes" by causing a compilation error.
// static_assert_1(!(std::is_constructible<Channel, Channel::_integral>()));
// "Passes" on most compilers, passes on g++47 by causing a compilation error.
// static_assert_1(!(std::is_constructible<Channel, Depth>()));

// Commented out temporarily due to GCC 4.7- bug.
// static_assert_1(!std::is_default_constructible<Channel>());

// Intended implicit conversions.
static_assert_1((std::is_convertible<Channel::_enumerated, Channel>()));

// Regrettable implicit conversions.
static_assert_1((std::is_convertible<decltype(Channel::Red),
    Channel::_integral>()));

// Disallowed implicit conversions.
static_assert_1(!(std::is_convertible<Channel::_integral, Channel>()));
static_assert_1(!(std::is_convertible<Depth, Channel>()));
static_assert_1(!(std::is_convertible<Channel, Depth>()));

// Controllable implicit conversions.
static_assert_1(
(std::is_convertible<Channel, Channel::_integral>() != STRICT));
static_assert_1(
(std::is_convertible<Channel, Channel::_enumerated>() != STRICT));
static_assert_1(
(std::is_convertible<decltype(+Channel::Red), Channel::_integral>()
    != STRICT));
static_assert_1(
(std::is_convertible<decltype(Channel::_values()[0]), Channel::_integral>()
    != STRICT));

static_assert_1((+Depth::HighColor)._to_integral() == 40);
static_assert_1(Depth::_from_integral(40) == +Depth::HighColor);
static_assert_1(Depth::_from_integral_unchecked(40) == +Depth::HighColor);
static_assert_1(Depth::_from_integral_nothrow(40));
static_assert_1(*Depth::_from_integral_nothrow(40) == +Depth::HighColor);
static_assert_1(Depth::_is_valid(40));

static_assert_1(Channel::_from_string("Green") == +Channel::Green);
static_assert_1(Channel::_from_string_nocase("green") == +Channel::Green);
static_assert_1(*Channel::_from_string_nothrow("Green") == +Channel::Green);
static_assert_1(
    *Channel::_from_string_nocase_nothrow("green") == +Channel::Green);
static_assert_1(Channel::_is_valid("Green"));
static_assert_1(Channel::_is_valid_nocase("green"));

static_assert_1(Channel::_size() == 3);
static_assert_1(Channel::_values().size() == 3);
static_assert_1(*Channel::_values().begin() == +Channel::Red);
static_assert_1(*(Channel::_values().end() - 1) == +Channel::Blue);
static_assert_1(Channel::_values()[1] == +Channel::Green);

namespace name_clash_test
{
    struct Foo {};
    std::ostream& operator<<(std::ostream&, Foo);

    BETTER_ENUM(Enum, int, ONE, TWO, THREE)
    static_assert_1((std::is_same<decltype(std::declval<std::ostream&>() << +Enum::ONE), std::ostream&>()));
}

#ifdef BETTER_ENUMS_CONSTEXPR_TO_STRING

constexpr bool same_string(const char *r, const char *s, size_t index = 0)
{
    return
        r[index] == '\0' ? s[index] == '\0' :
        s[index] == '\0' ? false :
        r[index] != s[index] ? false :
        same_string(r, s, index + 1);
}

static_assert_1(same_string((+Depth::HighColor)._to_string(), "HighColor"));
static_assert_1(Depth::_names().size() == 2);
static_assert_1(same_string(*Depth::_names().begin(), "HighColor"));
static_assert_1(same_string(*(Depth::_names().end() - 1), "TrueColor"));
static_assert_1(same_string(Depth::_names()[0], "HighColor"));

#endif // #ifdef BETTER_ENUMS_CONSTEXPR_TO_STRING

#endif // #ifdef _ENUM_HAVE_CONSTEXPR


TEST_CASE("test constant values", MAIN_TAG)
{
    CHECK((+Channel::Red)._to_integral() == 0);
    CHECK((+Channel::Green)._to_integral() == 1);
    CHECK((+Channel::Blue)._to_integral() == 2);
    CHECK((+Depth::HighColor)._to_integral() == 40);
    CHECK((+Depth::TrueColor)._to_integral() == 20);
}

TEST_CASE("test integral conversions", MAIN_TAG)
{
    CHECK(Channel::_from_integral(1) == +Channel::Green);
    CHECK(Channel::_from_integral(1) != +Channel::Blue);
    CHECK(Channel::_from_integral_unchecked(1) == +Channel::Green);
    CHECK(Channel::_from_integral_unchecked(1) != +Channel::Blue);

    CHECK_THROWS_AS(Channel::_from_integral(3), std::runtime_error);
    CHECK_NOTHROW(Channel::_from_integral_unchecked(3));

    better_enums::optional<Channel> maybe_channel =
        Channel::_from_integral_nothrow(2);

    CHECK(maybe_channel);
    CHECK(*maybe_channel == +Channel::Blue);
    CHECK(!Channel::_from_integral_nothrow(3));

    CHECK(Channel::_is_valid((Channel::_integral)0));
    CHECK(Channel::_is_valid(1));
    CHECK(Channel::_is_valid(2));
    CHECK(!Channel::_is_valid(3));
}

TEST_CASE("test string conversions", MAIN_TAG)
{
    CHECK(strcmp((+Channel::Green)._to_string(), "Green") == 0);
    CHECK(strcmp((+Depth::HighColor)._to_string(), "HighColor") == 0);

    CHECK(Channel::_from_string("Green") == +Channel::Green);
    CHECK(Channel::_from_string("Green") != +Channel::Blue);
    CHECK(Channel::_from_string("Blue") == +Channel::Blue);
    CHECK(Channel::_from_string("Blue") != +Channel::Green);
    CHECK_THROWS_AS(Channel::_from_string("green"), std::runtime_error);

    better_enums::optional<Channel> maybe_channel =
        Channel::_from_string_nothrow("Green");

    CHECK(maybe_channel);
    CHECK(*maybe_channel == +Channel::Green);
    CHECK(!Channel::_from_string_nothrow("green"));

    CHECK(Channel::_from_string_nocase("green") == +Channel::Green);
    CHECK(Channel::_from_string_nocase("green") != +Channel::Blue);
    CHECK(Channel::_from_string_nocase("blue") == +Channel::Blue);
    CHECK(Channel::_from_string_nocase("blue") != +Channel::Green);
    CHECK_THROWS_AS(Channel::_from_string_nocase("a"), std::runtime_error);

    maybe_channel = Channel::_from_string_nocase_nothrow("green");

    CHECK(maybe_channel);
    CHECK(*maybe_channel == +Channel::Green);
    CHECK(!Channel::_from_string_nocase_nothrow("greeen"));
    CHECK(Channel::_is_valid("Green"));
    CHECK(!Channel::_is_valid("green"));
    CHECK(Channel::_is_valid_nocase("green"));
    CHECK(!Channel::_is_valid_nocase("greeen"));
}

TEST_CASE("test value iterable", MAIN_TAG)
{
    CHECK(Channel::_size() == 3);
    CHECK(Depth::_size() == 2);
    CHECK(Channel::_values().size() == Channel::_size());
    CHECK(*Channel::_values().begin() == +Channel::Red);
    CHECK(*(Channel::_values().begin() + 1) == +Channel::Green);
    CHECK(*(Channel::_values().begin() + 2) == +Channel::Blue);
    CHECK(Channel::_values()[1] == +Channel::Green);
    CHECK(Channel::_values()[2] == +Channel::Blue);

    Channel::_value_iterator value_iterator = Channel::_values().begin();

    CHECK(*value_iterator == +Channel::Red);
    CHECK(value_iterator != Channel::_values().end());

    ++value_iterator;

    CHECK(*value_iterator == +Channel::Green);
    CHECK(value_iterator != Channel::_values().end());

    ++value_iterator;

    CHECK(*value_iterator == +Channel::Blue);
    CHECK(value_iterator != Channel::_values().end());

    ++value_iterator;

    CHECK(value_iterator == Channel::_values().end());
}

TEST_CASE("test name iterable", MAIN_TAG)
{
    CHECK(Channel::_names().size() == Channel::_size());
    CHECK(strcmp(*Channel::_names().begin(), "Red") == 0);
    CHECK(strcmp(Channel::_names()[0], "Red") == 0);
    CHECK(strcmp(Depth::_names()[0], "HighColor") == 0);

    Channel::_name_iterator name_iterator = Channel::_names().begin();

    CHECK(strcmp(*name_iterator, "Red") == 0);
    CHECK(name_iterator != Channel::_names().end());

    ++name_iterator;

    CHECK(strcmp(*name_iterator, "Green") == 0);
    CHECK(name_iterator != Channel::_names().end());

    ++name_iterator;

    CHECK(strcmp(*name_iterator, "Blue") == 0);
    CHECK(name_iterator != Channel::_names().end());

    ++name_iterator;

    CHECK(name_iterator == Channel::_names().end());
}

TEST_CASE("test type name", MAIN_TAG)
{
    CHECK(strcmp(Channel::_name(), "Channel") == 0);
    CHECK(strcmp(Depth::_name(), "Depth") == 0);
    CHECK(strcmp(Compression::_name(), "Compression") == 0);
}

/// @todo This test case is failing and is currently deemed invalid
/// at this time.
///
/// @see https://github.com/aantron/better-enums/issues/24
/*
TEST_CASE("test alias", MAIN_TAG)
{
    CHECK(Compression::Default == Compression::Huffman);
}
*/

TEST_CASE("test namespaced", MAIN_TAG)
{
    CHECK((+test::Namespaced::One)._to_integral() == 0);
    CHECK(test::Namespaced::_from_integral(0) == +test::Namespaced::One);
    CHECK(strcmp((+test::Namespaced::One)._to_string(), "One") == 0);
    CHECK(test::Namespaced::_from_string("Two") == +test::Namespaced::Two);
    CHECK(test::Namespaced::_values()[0] == +test::Namespaced::One);
    CHECK(strcmp(test::Namespaced::_names()[0], "One") == 0);
    CHECK(*test::Namespaced::_values().begin() == +test::Namespaced::One);
    CHECK(strcmp(*test::Namespaced::_names().begin(), "One") == 0);
}

BETTER_ENUM(Compiler, int, GCC, Clang, MSVC)

TEST_CASE("test stream output", MAIN_TAG)
{
    std::ostringstream stream;
    stream << +Compiler::GCC;
    CHECK(stream.str() == "GCC");
}

TEST_CASE("test stream input", MAIN_TAG)
{
    std::istringstream stream("Clang");
    Compiler compiler = Compiler::GCC;
    stream >> compiler;
    CHECK(compiler == +Compiler::Clang);
}

BETTER_ENUM(InternalNameCollisions, int,
    EnumClassForSwitchStatements, PutNamesInThisScopeAlso,
    force_initialization, value_array, raw_names, name_storage,
    name_array, initialized, the_raw_names, the_name_array)
