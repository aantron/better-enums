// This file was generated automatically

// Compile-time usage
//
// When used with $cxx11, Better Enums are generated entirely during
// compilation. All the data is available for use by your own constexpr
// functions. The examples in <em>this</em> tutorial aren't very useful, but
// read the following tutorials to get an idea of what can be done. Here, you
// will see the basics.

#include <iostream>

#ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
#define BETTER_ENUMS_CONSTEXPR_TO_STRING
#endif

#include <enum.h>

ENUM(Channel, int, Red = 1, Green = 2, Blue = 3)

constexpr Channel      channel = Channel::Green;
constexpr int          value = channel._to_integral();

constexpr const char   *name = channel._to_string();
constexpr Channel      parsed = Channel::_from_string("Red");

// All of the above are computed during compilation. You can do apparently
// useless things such as:

constexpr size_t length(const char *s, size_t index = 0)
{
    return s[index] == '\0' ? index : length(s, index + 1);
}

constexpr size_t    length_of_name_of_second_constant =
    length(Channel::_names()[1]);

int main()
{
    std::cout << length_of_name_of_second_constant << std::endl;

    return 0;
}

// Which prints "5", the length of "Green". That 5 was also computed during
// compilation.
