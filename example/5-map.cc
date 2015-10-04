// This file was generated automatically.

// Maps
//
// It is possible to create constexpr bidirectional maps between Better Enums
// and any type. This is currently an experimental feature. Feedback is very
// much wanted, but please don't build any mission-critical code on top of this
// :)
//
// The way it works is you give Better Enums a function - say, const char*
// describe(Channel). The library enumerates it to make a map.
//
// The reason for using a function is that a switch statement is, I believe, the
// only place where a compiler will check for exhaustiveness. If you forget to
// create a case for one of the enum's constants, the compiler can let you know.
// Obviously, a switch statement is not data, and needs to be inside a function.
// It can only be inside a constexpr function in C++14, so this feature is most
// natural in C++14. When you pass the function to Better Enums, the library can
// build up a lookup data structure at compile time.
//
// Actually, right now, Better Enums doesn't quite do that - it enumerates the
// function every time you want to convert to an enum (but not from an enum). It
// simply does a linear scan every time. This is because I haven't yet found a
// data structure whose compile-time generation is fast enough for practical
// use.


#include <iostream>
#include <enum.h>

BETTER_ENUM(Channel, int, Red, Green, Blue)

// We will create a map from this function:

constexpr const char* describe(Channel channel)
{
    switch(channel) {
        case Channel::Red:   return "the red channel";
        case Channel::Green: return "the green channel";
        case Channel::Blue:  return "the blue channel";
    }

    return "needed for gcc 5";
}

// Here is the map. The actual type is better_enums::map<Channel, const char*>.

constexpr auto descriptions = better_enums::make_map(describe);

// And the usage:

int main()
{
    std::cout << descriptions[Channel::Red] << std::endl;

    std::cout << descriptions.from_enum(Channel::Red) << std::endl;
    std::cout << descriptions.to_enum("the green channel") << std::endl;

    auto not_a_literal = std::string("the blue channel");
    std::cout << descriptions.to_enum(not_a_literal.c_str()) << std::endl;

    return 0;
}


// make_map above produces a value of type better_enums::map<E, T>. The full
// signature of the template better_enums::map is
//
// template <typename Enum, typename T, typename Compare = map_compare<T>>
//
// Compare has to be a class with a static member function bool less(const T&,
// const T&). The default implementation better_enums::map_compare simply
// applies operator <, except when T is const char*. In that case, it does
// lexicographic comparison.
