#include <iosfwd>
#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include <enum.h>

#define static_assert_1(e)  static_assert(e, #e)

#ifdef BETTER_ENUMS_STRICT_CONVERSION
#   define STRICT 1
#else
#   define STRICT 0
#endif



BETTER_ENUM(Channel, short, Red, Green, Blue)
BETTER_ENUM(Depth, short, HighColor = 40, TrueColor = 20)
BETTER_ENUM(Compression, short, None, Huffman, Default = Huffman)



namespace test {

BETTER_ENUM(Namespaced, short, One, Two)

}



// Using BETTER_ENUMS_HAVE_CONSTEXPR_ as a proxy for C++11 support. This should
// be changed to be more precise in the future.
#ifdef BETTER_ENUMS_HAVE_CONSTEXPR_

BETTER_ENUMS_DECLARE_STD_HASH(Channel)

#include <type_traits>
#include <functional>

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

namespace name_clash_test {

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



// Run-time testing.
class HashTests : public CxxTest::TestSuite {
  public:
    void test_same_values()
    {
#ifdef _ENUM_HAVE_CONSTEXPR
        TS_ASSERT_EQUALS(
            std::hash<Channel>().operator()(Channel::Red),
            std::hash<int>().operator()(0));
        TS_ASSERT_EQUALS(
            std::hash<Channel>().operator()(Channel::Green),
            std::hash<int>().operator()(1));
        TS_ASSERT_EQUALS(
            std::hash<Channel>().operator()(Channel::Blue),
            std::hash<int>().operator()(2));
#endif // #ifdef _ENUM_HAVE_CONSTEXPR
    }
};

class EnumTests : public CxxTest::TestSuite {
  public:
    void test_constant_values()
    {
        TS_ASSERT_EQUALS((+Channel::Red)._to_integral(), 0);
        TS_ASSERT_EQUALS((+Channel::Green)._to_integral(), 1);
        TS_ASSERT_EQUALS((+Channel::Blue)._to_integral(), 2);
        TS_ASSERT_EQUALS((+Depth::HighColor)._to_integral(), 40);
        TS_ASSERT_EQUALS((+Depth::TrueColor)._to_integral(), 20);
    }

    void test_integral_conversions()
    {
        TS_ASSERT_EQUALS(Channel::_from_integral(1), +Channel::Green);
        TS_ASSERT_DIFFERS(Channel::_from_integral(1), +Channel::Blue);
        TS_ASSERT_EQUALS(Channel::_from_integral_unchecked(1), +Channel::Green);
        TS_ASSERT_DIFFERS(Channel::_from_integral_unchecked(1), +Channel::Blue);

        TS_ASSERT_THROWS(Channel::_from_integral(3), std::runtime_error);
        TS_ASSERT_THROWS_NOTHING(Channel::_from_integral_unchecked(3));

        better_enums::optional<Channel> maybe_channel =
            Channel::_from_integral_nothrow(2);
        TS_ASSERT(maybe_channel);
        TS_ASSERT_EQUALS(*maybe_channel, +Channel::Blue);
        TS_ASSERT(!Channel::_from_integral_nothrow(3));

        TS_ASSERT(Channel::_is_valid((Channel::_integral)0));
        TS_ASSERT(Channel::_is_valid(1));
        TS_ASSERT(Channel::_is_valid(2));
        TS_ASSERT(!Channel::_is_valid(3));
    }

    void test_string_conversions()
    {
        TS_ASSERT_EQUALS(strcmp((+Channel::Green)._to_string(), "Green"), 0);
        TS_ASSERT_EQUALS(strcmp((+Depth::HighColor)._to_string(),
                         "HighColor"), 0);

        TS_ASSERT_EQUALS(Channel::_from_string("Green"), +Channel::Green);
        TS_ASSERT_DIFFERS(Channel::_from_string("Green"), +Channel::Blue);
        TS_ASSERT_EQUALS(Channel::_from_string("Blue"), +Channel::Blue);
        TS_ASSERT_DIFFERS(Channel::_from_string("Blue"), +Channel::Green);
        TS_ASSERT_THROWS(Channel::_from_string("green"), std::runtime_error);

        better_enums::optional<Channel> maybe_channel =
            Channel::_from_string_nothrow("Green");
        TS_ASSERT(maybe_channel);
        TS_ASSERT_EQUALS(*maybe_channel, +Channel::Green);
        TS_ASSERT(!Channel::_from_string_nothrow("green"));

        TS_ASSERT_EQUALS(Channel::_from_string_nocase("green"),
                         +Channel::Green);
        TS_ASSERT_DIFFERS(Channel::_from_string_nocase("green"),
                          +Channel::Blue);
        TS_ASSERT_EQUALS(Channel::_from_string_nocase("blue"),
                         +Channel::Blue);
        TS_ASSERT_DIFFERS(Channel::_from_string_nocase("blue"),
                          +Channel::Green);
        TS_ASSERT_THROWS(Channel::_from_string_nocase("a"), std::runtime_error);

        maybe_channel = Channel::_from_string_nocase_nothrow("green");
        TS_ASSERT(maybe_channel);
        TS_ASSERT_EQUALS(*maybe_channel, +Channel::Green);
        TS_ASSERT(!Channel::_from_string_nocase_nothrow("greeen"));

        TS_ASSERT(Channel::_is_valid("Green"));
        TS_ASSERT(!Channel::_is_valid("green"));
        TS_ASSERT(Channel::_is_valid_nocase("green"));
        TS_ASSERT(!Channel::_is_valid_nocase("greeen"));
    }

    void test_value_iterable()
    {
        TS_ASSERT_EQUALS(Channel::_size(), 3);
        TS_ASSERT_EQUALS(Depth::_size(), 2);
        TS_ASSERT_EQUALS(Channel::_values().size(), Channel::_size());
        TS_ASSERT_EQUALS(*Channel::_values().begin(), +Channel::Red);
        TS_ASSERT_EQUALS(*(Channel::_values().begin() + 1), +Channel::Green);
        TS_ASSERT_EQUALS(*(Channel::_values().begin() + 2), +Channel::Blue);
        TS_ASSERT_EQUALS(Channel::_values()[1], +Channel::Green);
        TS_ASSERT_EQUALS(Channel::_values()[2], +Channel::Blue);

        Channel::_value_iterator    value_iterator = Channel::_values().begin();
        TS_ASSERT_EQUALS(*value_iterator, +Channel::Red);
        TS_ASSERT_DIFFERS(value_iterator, Channel::_values().end());

        ++value_iterator;
        TS_ASSERT_EQUALS(*value_iterator, +Channel::Green);
        TS_ASSERT_DIFFERS(value_iterator, Channel::_values().end());

        ++value_iterator;
        TS_ASSERT_EQUALS(*value_iterator, +Channel::Blue);
        TS_ASSERT_DIFFERS(value_iterator, Channel::_values().end());

        ++value_iterator;
        TS_ASSERT_EQUALS(value_iterator, Channel::_values().end());
    }

    void test_name_iterable()
    {
        TS_ASSERT_EQUALS(Channel::_names().size(), Channel::_size());
        TS_ASSERT_EQUALS(strcmp(*Channel::_names().begin(), "Red"), 0);
        TS_ASSERT_EQUALS(strcmp(Channel::_names()[0], "Red"), 0);
        TS_ASSERT_EQUALS(strcmp(Depth::_names()[0], "HighColor"), 0);

        Channel::_name_iterator     name_iterator = Channel::_names().begin();
        TS_ASSERT_EQUALS(strcmp(*name_iterator, "Red"), 0);
        TS_ASSERT_DIFFERS(name_iterator, Channel::_names().end());

        ++name_iterator;
        TS_ASSERT_EQUALS(strcmp(*name_iterator, "Green"), 0);
        TS_ASSERT_DIFFERS(name_iterator, Channel::_names().end());

        ++name_iterator;
        TS_ASSERT_EQUALS(strcmp(*name_iterator, "Blue"), 0);
        TS_ASSERT_DIFFERS(name_iterator, Channel::_names().end());

        ++name_iterator;
        TS_ASSERT_EQUALS(name_iterator, Channel::_names().end());
    }

    void test_type_name()
    {
        TS_ASSERT_EQUALS(strcmp(Channel::_name(), "Channel"), 0);
        TS_ASSERT_EQUALS(strcmp(Depth::_name(), "Depth"), 0);
        TS_ASSERT_EQUALS(strcmp(Compression::_name(), "Compression"), 0);
    }

    void test_alias()
    {
        TS_ASSERT_EQUALS(Compression::Default, Compression::Huffman);
    }

    void test_namespaced()
    {
        TS_ASSERT_EQUALS((+test::Namespaced::One)._to_integral(), 0);
        TS_ASSERT_EQUALS(test::Namespaced::_from_integral(0),
                         +test::Namespaced::One);
        TS_ASSERT_EQUALS(strcmp((+test::Namespaced::One)._to_string(), "One"),
                         0);
        TS_ASSERT_EQUALS(test::Namespaced::_from_string("Two"),
                         +test::Namespaced::Two);

        TS_ASSERT_EQUALS(test::Namespaced::_values()[0],
                         +test::Namespaced::One);
        TS_ASSERT_EQUALS(strcmp(test::Namespaced::_names()[0], "One"), 0);

        TS_ASSERT_EQUALS(*test::Namespaced::_values().begin(),
                         +test::Namespaced::One);
        TS_ASSERT_EQUALS(strcmp(*test::Namespaced::_names().begin(), "One"), 0);
    }

    void test_to_index()
    {
        TS_ASSERT_EQUALS((+Channel::Red)._to_index(), 0);
        TS_ASSERT_EQUALS((+Channel::Green)._to_index(), 1);
        TS_ASSERT_EQUALS((+Channel::Blue)._to_index(), 2);

        TS_ASSERT_EQUALS((+Depth::HighColor)._to_index(), 0);
        TS_ASSERT_EQUALS((+Depth::TrueColor)._to_index(), 1);

        TS_ASSERT_EQUALS((+Compression::None)._to_index(), 0);
        TS_ASSERT_EQUALS((+Compression::Huffman)._to_index(), 1);
//        TS_ASSERT_EQUALS((+Compression::Default)._to_index(), 2); // This won't pass as Compression::Huffman == Compression::Default
    }

	void test_from_index()
	{
        TS_ASSERT_EQUALS((+Channel::Red), Channel::_from_index(0));
        TS_ASSERT_EQUALS((+Channel::Green), Channel::_from_index(1));
        TS_ASSERT_EQUALS((+Channel::Blue), Channel::_from_index(2));
        TS_ASSERT_THROWS(Channel::_from_index(42), std::runtime_error);

        TS_ASSERT_EQUALS((+Depth::HighColor), Depth::_from_index(0));
        TS_ASSERT_EQUALS((+Depth::TrueColor), Depth::_from_index(1));
        TS_ASSERT_THROWS(Depth::_from_index(42), std::runtime_error);

        TS_ASSERT_EQUALS((+Compression::None), Compression::_from_index(0));
        TS_ASSERT_EQUALS((+Compression::Huffman), Compression::_from_index(1));
        TS_ASSERT_EQUALS((+Compression::Default), Compression::_from_index(2));
        TS_ASSERT_THROWS(Compression::_from_index(42), std::runtime_error);
	}

    void test_from_index_nothrow()
    {
		better_enums::optional<Channel> maybe_channel = Channel::_from_index_nothrow(0);
        TS_ASSERT(maybe_channel);
        TS_ASSERT_EQUALS(*maybe_channel, +Channel::Red);

		maybe_channel = Channel::_from_index_nothrow(1);
        TS_ASSERT(maybe_channel);
        TS_ASSERT_EQUALS(*maybe_channel, +Channel::Green);

		maybe_channel = Channel::_from_index_nothrow(2);
        TS_ASSERT(maybe_channel);
        TS_ASSERT_EQUALS(*maybe_channel, +Channel::Blue);

		maybe_channel = Channel::_from_index_nothrow(45);
		TS_ASSERT(!maybe_channel);

		better_enums::optional<Depth> maybe_depth = Depth::_from_index_nothrow(0);
        TS_ASSERT(maybe_depth);
        TS_ASSERT_EQUALS(*maybe_depth, +Depth::HighColor);

		maybe_depth = Depth::_from_index_nothrow(1);
        TS_ASSERT(maybe_depth);
        TS_ASSERT_EQUALS(*maybe_depth, +Depth::TrueColor);

		maybe_depth = Depth::_from_index_nothrow(45);
		TS_ASSERT(!maybe_depth);

		better_enums::optional<Compression> maybe_compression = Compression::_from_index_nothrow(0);
        TS_ASSERT(maybe_compression);
        TS_ASSERT_EQUALS(*maybe_compression, +Compression::None);

		maybe_compression = Compression::_from_index_nothrow(1);
        TS_ASSERT(maybe_compression);
        TS_ASSERT_EQUALS(*maybe_compression, +Compression::Huffman);

		maybe_compression = Compression::_from_index_nothrow(2);
        TS_ASSERT(maybe_compression);
        TS_ASSERT_EQUALS(*maybe_compression, +Compression::Default);

		maybe_compression = Compression::_from_index_nothrow(45);
		TS_ASSERT(!maybe_compression);
    }

	void test_from_index_unchecked()
	{

        TS_ASSERT_EQUALS((+Channel::Red), Channel::_from_index_unchecked(0));
        TS_ASSERT_EQUALS((+Channel::Green), Channel::_from_index_unchecked(1));
        TS_ASSERT_EQUALS((+Channel::Blue), Channel::_from_index_unchecked(2));

        TS_ASSERT_EQUALS((+Depth::HighColor), Depth::_from_index_unchecked(0));
        TS_ASSERT_EQUALS((+Depth::TrueColor), Depth::_from_index_unchecked(1));

        TS_ASSERT_EQUALS((+Compression::None), Compression::_from_index_unchecked(0));
        TS_ASSERT_EQUALS((+Compression::Huffman), Compression::_from_index_unchecked(1));
        TS_ASSERT_EQUALS((+Compression::Default), Compression::_from_index_unchecked(2));
	}
};



BETTER_ENUM(InternalNameCollisions, int,
            EnumClassForSwitchStatements, PutNamesInThisScopeAlso,
            force_initialization, value_array, raw_names, name_storage,
            name_array, initialized, the_raw_names, the_name_array)
