// Usage in constexpr expressions. All members of an ENUM are constexpr when
// given constant arguments, with the exception of _to_string and dereferencing
// the _names iterator.

#include <iostream>
#include <enum.h>

ENUM(Channel, int, Red, Green, Blue);

// Initialization.
constexpr Channel   channel_1 = Channel::Green;

constexpr Channel   channel_4 = enum_::from_integral<Channel>(2);

constexpr Channel   channel_2 = enum_::from_string<Channel>("Blue");
constexpr Channel   channel_3 = enum_::from_string_nocase<Channel>("gReEn");

// Conversion to integer (but not to string).
constexpr int       channel_1_representation = enum_::to_integral(channel_1);

// Validity checks (including against strings).
constexpr bool      should_be_valid_1 = enum_::traits<Channel>::is_valid(2);
constexpr bool      should_be_invalid_1 = enum_::traits<Channel>::is_valid(42);

constexpr bool      should_be_valid_2 = enum_::traits<Channel>::is_valid("Red");
constexpr bool      should_be_invalid_2 =
    enum_::traits<Channel>::is_valid("red");

constexpr bool      should_be_valid_3 =
    enum_::traits<Channel>::is_valid_nocase("red");
constexpr bool      should_be_invalid_3 =
    enum_::traits<Channel>::is_valid_nocase("reed");

// _names and _values collections and iterator creation.
constexpr Channel   channel_5 = *enum_::traits<Channel>::values.begin();
constexpr auto      name_iterator = enum_::traits<Channel>::names.begin();

// Range properties.
constexpr Channel   channel_6 = enum_::traits<Channel>::max;
constexpr size_t    span = enum_::traits<Channel>::span;

// Type name.
constexpr auto      name = enum_::traits<Channel>::name;

// Explicit promotion.
constexpr int       converted = enum_::to_integral(Channel::Green);



// The above, printed for verification.
void print_channel(int number, Channel channel)
{
    std::cout
        << "channel_"
        << number
        << " is "
        << enum_::to_string(channel)
        << std::endl;
}

#define PRINT(n)    print_channel(n, channel_ ## n)

void print_validity(bool expected, bool actual)
{
    std::cout
        << "should be "
        << expected
        << ": "
        << actual
        << std::endl;
}

int main()
{
    PRINT(1);
    PRINT(2);
    PRINT(3);
    PRINT(4);

    print_validity(true, should_be_valid_1);
    print_validity(false, should_be_invalid_1);
    print_validity(true, should_be_valid_2);
    print_validity(false, should_be_invalid_2);
    print_validity(true, should_be_valid_3);
    print_validity(false, should_be_invalid_3);

    PRINT(5);
    PRINT(6);

    std::cout << *name_iterator << std::endl;
    std::cout << "span: " << span << std::endl;
    std::cout << "type name: " << name << std::endl;

    return 0;
}
