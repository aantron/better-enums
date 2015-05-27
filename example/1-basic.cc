// Basic conversions to/from strings and the underlying integral type.

#include <iostream>
#include <enum.h>

ENUM(Channel, uint16_t, Red, Green = 2, Blue, Alias = Red)

// Enums should be treated like integers (in memory, Channel is a uint16_t), and
// should generally be passed by value.
void print_channel(Channel channel)
{
    std::cout
        << "channel \'"
        << channel.to_string()
        << "\' has value "
        << channel.to_integral()
        << std::endl;
}

int main()
{
    // A value must be assigned upon construction.
    Channel     channel = Channel::Green;
    print_channel(channel);

    // This will not work, though see example/6-traits.cc for an alternative.
    // Channel     default_constructed_channel;



    // Conversions from strings and the integral type. Static members of Channel
    // are prefixed with _ to avoid conflicts with constant names.
    // _from_integral is a checked cast.
    channel = Channel::_from_integral(0);
    print_channel(channel);

    channel = Channel::_from_string("Blue");
    print_channel(channel);

    channel = Channel::_from_string_nocase("bluE");
    print_channel(channel);



    // Failed conversions.
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



    // Conversions with the nothrow (optional) interface.
    auto    maybe_channel = Channel::_from_string_nothrow("foo");
    if (maybe_channel)
        throw std::logic_error("expected conversion failure");

    maybe_channel = Channel::_from_string_nothrow("Blue");
    if (!maybe_channel)
        throw std::logic_error("expected successful conversion");
    print_channel(*maybe_channel);



    // Unsafe unchecked cast.
    channel = Channel::_from_integral_unchecked(2);



    // Direct operations on a constant require a promotion with the unary +
    // operator. This is an implementation artifact - constants are not actually
    // values of type Channel, but of type Channel::_Enumerated, and the
    // compiler isn't always able to implicitly promote the latter to the
    // former. + is used to force the promotion.
    std::cout << (+Channel::Green).to_string() << std::endl;

    // This will not work.
    // std::cout << (Channel::Green).to_string() << std::endl;



    // The type name is available as a string.
    std::cout << Channel::_name << std::endl;



    return 0;
}

static_assert(sizeof(Channel) == sizeof(uint16_t),
              "enum has the same size as its underlying integral type");

static_assert(alignof(Channel) == alignof(uint16_t),
              "enum has the same alignment as its underlying integral type");

static_assert(std::is_same<Channel::_Integral, uint16_t>(),
              "the underlying integral type is accessible as a member");
