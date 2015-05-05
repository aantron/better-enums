// Basic conversions to/from strings and the underlying integral type.

#include <iostream>
#include <enum.h>

ENUM(Channel, uint8_t, Red, Green = 2, Blue, Alias = Red);

void print_channel(Channel channel)
{
    std::cout
        << "channel \'"
        << channel.to_string()
        << "\' has value "
        << (int)channel.to_integral() << std::endl;
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
    channel = Channel::_from_integral(0);
    print_channel(channel);

    channel = Channel::_from_string("Blue");
    print_channel(channel);

    channel = Channel::_from_string_nocase("bluE");
    print_channel(channel);



    // Bad conversions.
    try {
        channel = Channel::_from_integral(15);
        throw std::logic_error("expected an exception");
    }
    catch (const std::runtime_error &e) { }

    try {
        channel = Channel::_from_string("Purple");
        throw std::logic_error("expected an exception");
    }
    catch (const std::runtime_error &e) { }

    try {
        channel = Channel::_from_string_nocase("bluee");
        throw std::logic_error("expected an exception");
    }
    catch (const std::runtime_error &e) { }



    // Unsafe unchecked cast.
    channel = Channel::_from_integral_unchecked(2);



    // Direct conversion of a constant unfortunately requires an explicit
    // promotion.
    std::cout << (+Channel::Green).to_string() << std::endl;



    // The type name is available as a string.
    std::cout << Channel::_name << std::endl;



    return 0;
}

static_assert(sizeof(Channel) == sizeof(uint8_t),
              "enum has the same size as its underlying integral type");

static_assert(alignof(Channel) == alignof(uint8_t),
              "enum has the same alignment as its underlying integral type");

static_assert(std::is_same<Channel::_Integral, uint8_t>(),
              "the underlying integral type is accessible as a member");
