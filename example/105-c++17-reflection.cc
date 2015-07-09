// This file was generated automatically.

// C++17 reflection
//
// Better Enums can be used to approximately implement the enums portion of the
// C++17 reflection proposal N4428 in C++11. The implementation is approximate
// in the following senses:
//
//   1. It only applies to Better Enums, not built-in enums.
//   2. enum_traits<E>::enumerators::get<I>::identifier is a non-constexpr
//      function rather than a constexpr variable. I could make it a constexpr
//      variable as in the proposal, but that requires compile-time name
//      trimming to be enabled for the Better Enum on which get is used. Since
//      that's an opt-in feature, I can't guarantee it. I preferred not to write
//      feature-detection code, in order to keep the implementation simple.
//   3. The return type of identifier is const char* instead of the proposed
//      std::string_literal, because I don't have an implementation of the
//      latter available. I'm also ignoring the requirements on encoding, and
//      just taking whatever the preprocessor provides.
//
// With that out of the way, we can look at an example.

// The implementation is defined in extra/better-enums/n4428.h. Let's assume
// that extra/ has been added as an include file path.

#include <iostream>
#include <enum.h>
#include <better-enums/n4428.h>


// Let's declare an enum:

ENUM(Channel, char, Red = 1, Green, Blue)

// N4428 requires three constexpr traits, of which we have two implemented
// exactly, that is, as constexpr:

constexpr std::size_t   size =
    std::enum_traits<Channel>::enumerators::size;

constexpr Channel       value_0 =
    std::enum_traits<Channel>::enumerators::get<0>::value;
constexpr Channel       value_1 =
    std::enum_traits<Channel>::enumerators::get<1>::value;

// Let's check the results:

static_assert(size == 3, "");

static_assert(value_0 == +Channel::Red, "");
static_assert(value_1 == +Channel::Green, "");

// Finally, we can try using identifier:

int main()
{
    std::cout
        << std::enum_traits<Channel>::enumerators::get<2>::identifier()
        << std::endl;

    return 0;
}
