// Usage in constexpr expressions. All members of an ENUM are constexpr when
// given constant arguments. Iterators can be advanced at compile time by adding
// 1 (note - this means using "+ 1", not "++". The "++" operator is not
// constexpr).

// #define BETTER_ENUMS_FORCE_CONSTEXPR_TO_STRING

#include <iostream>
#include <enum.h>

CONSTEXPR_TO_STRING_ENUM(Channel, int, Red, Green = 2, Blue)

// Initialization.
constexpr Channel       channel_1 = Channel::Green;

constexpr Channel       channel_4 = Channel::_from_integral(2);

constexpr Channel       channel_2 = Channel::_from_string("Blue");
constexpr Channel       channel_3 = Channel::_from_string_nocase("gReEn");

// Conversions to integers and strings.
constexpr int           channel_1_representation = channel_1._to_integral();
constexpr const char    *channel_1_name = channel_1._to_string();

// Validity checks (including against strings).
constexpr bool          should_be_valid_1 = Channel::_is_valid(2);
constexpr bool          should_be_invalid_1 = Channel::_is_valid(42);

constexpr bool          should_be_valid_2 = Channel::_is_valid("Red");
constexpr bool          should_be_invalid_2 = Channel::_is_valid("red");

constexpr bool          should_be_valid_3 = Channel::_is_valid_nocase("red");
constexpr bool          should_be_invalid_3 = Channel::_is_valid_nocase("reed");

// _names and _values collections and iterators.
constexpr Channel       channel_5 = *(Channel::_values().begin() + 1);
constexpr const char    *name_through_iterator =
                                            *(Channel::_names().begin() + 1);
constexpr const char    *name_through_subscript = Channel::_names()[2];

// Type name.
constexpr auto          name = Channel::_name();

// Explicit promotion.
constexpr int           converted = (+Channel::Green)._to_integral();



// The above, printed for verification.
void print_channel(int number, Channel channel)
{
    std::cout
        << "channel_"
        << number
        << " is "
        << channel._to_string()
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

    std::cout << "constexpr trimmed name: " << channel_1_name << std::endl;
    std::cout << "constexpr name through iterator: "
              << name_through_iterator << std::endl;
    std::cout << "constexpr name through suscript: "
              << name_through_subscript << std::endl;
    std::cout << "type name: " << name << std::endl;

    return 0;
}
