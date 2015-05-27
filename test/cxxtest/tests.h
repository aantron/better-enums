#include <stdexcept>
#include <type_traits>
#include <cxxtest/TestSuite.h>
#include <enum.h>

#define static_assert_1(e)  static_assert(e, #e)



ENUM(Channel, short, Red, Green, Blue)
ENUM(Depth, short, HighColor = 40, TrueColor = 20)
ENUM(Compression, short, None, Huffman, Default = Huffman)



// Type properties.
static_assert_1(std::is_class<Channel>());
static_assert_1(std::is_trivial<Channel>());
static_assert_1(std::is_standard_layout<Channel>());
static_assert_1(std::is_pod<Channel>());
static_assert_1(std::is_literal_type<Channel>());



// Member type properties and identities.
static_assert_1(std::is_integral<Channel::_Integral>());
static_assert_1(std::is_enum<Channel::_Enumerated>());

static_assert_1((std::is_same<short, Channel::_Integral>()));
static_assert_1((std::is_same<
    short, std::underlying_type<Channel::_Enumerated>::type>()));

static_assert_1(!(std::is_same<int, Channel::_Integral>()));
static_assert_1(!(std::is_same<
    int, std::underlying_type<Channel::_Enumerated>::type>()));

static_assert_1(sizeof(Channel) == sizeof(short));
static_assert_1(alignof(Channel) == alignof(short));

static_assert_1((std::is_same<decltype(Channel::Red), Channel::_Enumerated>()));



// Supported constructors.
static_assert_1(!std::is_default_constructible<Channel>());

#ifdef __clang__
static_assert_1(std::is_trivially_copyable<Channel>());
#endif

static_assert_1((std::is_constructible<Channel, Channel::_Enumerated>()));
static_assert_1(!(std::is_constructible<Channel, Channel::_Integral>()));
static_assert_1(!(std::is_constructible<Channel, Depth>()));



// Intended implicit conversions.
static_assert_1((std::is_convertible<Channel::_Enumerated, Channel>()));

// Regrettable implicit conversions.
static_assert_1((std::is_convertible<decltype(Channel::Red),
                                     Channel::_Integral>()));

// Disallowed implicit conversions.
static_assert_1(!(std::is_convertible<Channel::_Integral, Channel>()));
static_assert_1(!(std::is_convertible<Channel, Channel::_Integral>()));
static_assert_1(!(std::is_convertible<Depth, Channel>()));
static_assert_1(!(std::is_convertible<Channel, Depth>()));
static_assert_1(!(std::is_convertible<Channel, Channel::_Enumerated>()));
static_assert_1(!(std::is_convertible<decltype(+Channel::Red),
                                      Channel::_Integral>()));
static_assert_1(!(std::is_convertible<decltype(Channel::_values[0]),
                                      Channel::_Integral>()));



// Constant values.
static_assert_1((+Channel::Red).to_integral() == 0);
static_assert_1((+Channel::Green).to_integral() == 1);
static_assert_1((+Channel::Blue).to_integral() == 2);
static_assert_1((+Depth::HighColor).to_integral() == 40);
static_assert_1((+Depth::TrueColor).to_integral() == 20);



// Integral conversions.
static_assert_1(Channel::_from_integral(1) == Channel::Green);
static_assert_1(Channel::_from_integral(1) != Channel::Blue);
static_assert_1(Channel::_from_integral_unchecked(1) == Channel::Green);
static_assert_1(Channel::_from_integral_unchecked(1) != Channel::Blue);

static_assert_1(Channel::_is_valid((Channel::_Integral)0));
static_assert_1(Channel::_is_valid(1));
static_assert_1(Channel::_is_valid(2));
static_assert_1(!Channel::_is_valid(3));



// String conversions.
static_assert_1(Channel::_from_string("Green") == Channel::Green);
static_assert_1(Channel::_from_string("Green") != Channel::Blue);
static_assert_1(Channel::_from_string("Blue") == Channel::Blue);
static_assert_1(Channel::_from_string("Blue") != Channel::Green);

static_assert_1(Channel::_from_string_nocase("green") == Channel::Green);
static_assert_1(Channel::_from_string_nocase("green") != Channel::Blue);
static_assert_1(Channel::_from_string_nocase("blue") == Channel::Blue);
static_assert_1(Channel::_from_string_nocase("blue") != Channel::Green);

static_assert_1(Channel::_is_valid("Green"));
static_assert_1(!Channel::_is_valid("green"));
static_assert_1(Channel::_is_valid_nocase("green"));
static_assert_1(!Channel::_is_valid_nocase("greeen"));



// Iterables.
static_assert_1(Channel::_size == 3);
static_assert_1(Depth::_size == 2);
static_assert_1(Channel::_values.size() == Channel::_size);
static_assert_1(*Channel::_values.begin() == Channel::Red);
static_assert_1(*(Channel::_values.begin() + 1) == Channel::Green);
static_assert_1(*(Channel::_values.begin() + 2) == Channel::Blue);
static_assert_1(Channel::_values[1] == Channel::Green);
static_assert_1(Channel::_values[2] == Channel::Blue);

static_assert_1(Channel::_names.size() == Channel::_size);
// The next one is a little janky, but actually the pointers should be the same.
static_assert_1(*Channel::_names.begin() == (+Channel::Red).to_string());



// Aliases.
static_assert_1(Compression::Default == Compression::Huffman);



// Run-time testing.
class EnumTests : public CxxTest::TestSuite {
  public:
    void test_bad_integral_conversions()
    {
        TS_ASSERT_THROWS(Channel::_from_integral(3), std::runtime_error);
        TS_ASSERT_THROWS_NOTHING(Channel::_from_integral_unchecked(3));
    }

    void test_string_conversions()
    {
        TS_ASSERT_EQUALS(strcmp((+Channel::Green).to_string(), "Green"), 0);
        TS_ASSERT_EQUALS(strcmp((+Depth::HighColor).to_string(),
                         "HighColor"), 0);

        TS_ASSERT_THROWS(Channel::_from_string("green"), std::runtime_error);
        TS_ASSERT_THROWS(Channel::_from_string_nocase("a"), std::runtime_error);
    }

    void test_value_iterable()
    {
        auto    value_iterator = Channel::_values.begin();
        TS_ASSERT_EQUALS(*value_iterator, Channel::Red);
        TS_ASSERT_DIFFERS(value_iterator, Channel::_values.end());

        ++value_iterator;
        TS_ASSERT_EQUALS(*value_iterator, Channel::Green);
        TS_ASSERT_DIFFERS(value_iterator, Channel::_values.end());

        ++value_iterator;
        TS_ASSERT_EQUALS(*value_iterator, Channel::Blue);
        TS_ASSERT_DIFFERS(value_iterator, Channel::_values.end());

        ++value_iterator;
        TS_ASSERT_EQUALS(value_iterator, Channel::_values.end());
    }

    void test_name_iterable()
    {
        auto    name_iterator = Channel::_names.begin();
        TS_ASSERT_EQUALS(strcmp(*name_iterator, "Red"), 0);
        TS_ASSERT_DIFFERS(name_iterator, Channel::_names.end());

        ++name_iterator;
        TS_ASSERT_EQUALS(strcmp(*name_iterator, "Green"), 0);
        TS_ASSERT_DIFFERS(name_iterator, Channel::_names.end());

        ++name_iterator;
        TS_ASSERT_EQUALS(strcmp(*name_iterator, "Blue"), 0);
        TS_ASSERT_DIFFERS(name_iterator, Channel::_names.end());

        ++name_iterator;
        TS_ASSERT_EQUALS(name_iterator, Channel::_names.end());
    }

    void test_type_name()
    {
        TS_ASSERT_EQUALS(strcmp(Channel::_name, "Channel"), 0);
        TS_ASSERT_EQUALS(strcmp(Depth::_name, "Depth"), 0);
        TS_ASSERT_EQUALS(strcmp(Compression::_name, "Compression"), 0);
    }
};
