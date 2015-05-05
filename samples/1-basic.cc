// Basic conversions to/from strings and the underlying integral type.

#include <iostream>
#include <enum.h>

ENUM(Channel, uint8_t, Red, Green = 2, Blue, Alias = Channel::Red);

void print_channel(Channel channel)
{
    std::cout
        << "channel \'"
        << enum_::to_string(channel)
        << "\' has value "
        << enum_::to_integral(channel)
        << std::endl;
}

int main()
{
    // A value must be assigned upon construction.
    Channel     channel = Channel::Green;
    print_channel(channel);

    // This will not work.
    // Channel     default_constructed_channel;



    // Conversions from strings and the integral type. Function names are
    // prefixed with _ to avoid conflicts with constant names. _from_integral is
    // a checked cast.
    channel = enum_::from_integral<Channel>(0);
    print_channel(channel);

    channel = enum_::from_string<Channel>("Blue");
    print_channel(channel);

    channel = enum_::from_string_nocase<Channel>("bluE");
    print_channel(channel);



    // Bad conversions.
    try {
        channel = enum_::from_integral<Channel>(15);
        throw std::logic_error("expected an exception");
    }
    catch (const std::runtime_error &e) { }

    try {
        channel = enum_::from_string<Channel>("Purple");
        throw std::logic_error("expected an exception");
    }
    catch (const std::runtime_error &e) { }

    try {
        channel = enum_::from_string_nocase<Channel>("bluee");
        throw std::logic_error("expected an exception");
    }
    catch (const std::runtime_error &e) { }



    // Unsafe unchecked cast.
    channel = enum_::from_integral_unchecked<Channel>(2);



    // Direct conversion of a constant unfortunately requires an explicit
    // promotion.
    std::cout << enum_::to_string(Channel::Green) << std::endl;



    // The type name is available as a string.
    std::cout << enum_::traits<Channel>::name << std::endl;



    return 0;
}

static_assert(std::is_same<enum_::traits<Channel>::Integral, uint8_t>(),
              "the underlying integral type is accessible as a member");
