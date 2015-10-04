// This file was generated automatically.

// Conversions
//
// Let's begin by including enum.h and declaring our enum:

#include <cassert>
#include <iostream>

#include <enum.h>

BETTER_ENUM(Channel, int, Cyan = 1, Magenta, Yellow, Black)

// We now have an int-sized enum with four constants.
//
// There are three groups of conversion functions: for strings, case-insensitive
// strings, and integers. They all follow the same pattern, so I'll explain the
// string functions in detail, and the rest can be understood by analogy.
//
// Strings
//
// There are three functions:
//
//   1. ._to_string
//   2. ::_from_string
//   3. ::_from_string_nothrow

int main()
{
    Channel     channel = Channel::Cyan;
    std::cout << channel._to_string() << " ";

// As you'd expect, the code above prints "Cyan".
//
// If channel is invalid - for example, if you simply cast the number "42" to
// Channel - then the result of to_string is undefined.


    channel = Channel::_from_string("Magenta");
    std::cout << channel._to_string() << " ";

// This is also straightforward. If you pass a string which is not the name of a
// declared value, _from_string throws std::runtime_error.

// If you don't want an exception, there is _from_string_nothrow:

    better_enums::optional<Channel> maybe_channel =
        Channel::_from_string_nothrow("Yellow");

    if (!maybe_channel)
        std::cout << "error";
    else
        std::cout << maybe_channel->_to_string() << " ";

// This returns an optional value, in the style of boost::optional or the
// proposed std::optional.
//
// What that means for the above code is:
//
//   1. if the conversion succeeds, maybe_channel converts to true and
//      *maybe_channel is the converted value of type Channel,
//   2. if the conversion fails, maybe_channel converts to false.
//
// In C++11, you can use auto to avoid writing out the optional type:
//
//     auto        maybe_channel = Channel::_from_string_nothrow("Yellow");
//     if (!maybe_channel)
//         std::cout << "error";
//     else
//         std::cout << maybe_channel->_to_string() << " ";
//
// Case-insensitive strings
//
// The "_nocase" string conversions follow the same pattern, except for the lack
// of a "to_string_nocase".
//
//   1. ::_from_string_nocase
//   2. ::_from_string_nocase_nothrow

    channel = Channel::_from_string_nocase("cYaN");
    std::cout << channel._to_string() << " ";

    maybe_channel = Channel::_from_string_nocase_nothrow("rEeD");
    assert(!maybe_channel);

// Integers
//
// And, it is similar with the representation type int:
//
//   1. ._to_integral
//   2. ::_from_integral
//   3. ::_from_integral_nothrow
//   4. ::_from_integral_unchecked

    channel = Channel::Cyan;
    std::cout << channel._to_integral() << " ";

    channel = Channel::_from_integral(2);
    std::cout << channel._to_string() << " ";

    maybe_channel = Channel::_from_integral_nothrow(0);
    assert(!maybe_channel);

// That prints "1 Magenta".
//
// _from_integral_unchecked is a no-op unchecked cast of integers to enums, so
// use it carefully.

    channel = Channel::_from_integral_unchecked(0);
    // Invalid - better not to try converting it to string!

// Validity checking
//
// For completeness, Better Enums also provides three validity checking
// functions, one for each of the groups of conversions - string,
// case-insensitive string, and integer:

    assert(Channel::_is_valid(3));
    assert(Channel::_is_valid("Magenta"));
    assert(Channel::_is_valid_nocase("cYaN"));


// Almost done.
//
// There is one unfortunate wrinkle. You cannot convert a literal constant such
// as Channel::Cyan directly to, for example, a string. You have to prefix it
// with +:

    std::cout << (+Channel::Cyan)._to_string();

// This is due to some type gymnastics in the implementation of Better Enums.
// The reference has a full explanation.


    std::cout << std::endl;
    return 0;
}
