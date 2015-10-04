// This file was generated automatically.

// Compile-time usage
//
// When used with C++11, Better Enums are generated entirely during compilation.
// All the data is available for use by your own constexpr functions. The
// examples in this tutorial aren't very useful, but look at the demos at the
// bottom of the main page to get an idea of what can be done. Here, you will
// see the basics.

#include <iostream>

// The reason for this is explained below.
#ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
#define BETTER_ENUMS_CONSTEXPR_TO_STRING
#endif

#include <enum.h>

BETTER_ENUM(Channel, int, Red = 1, Green = 2, Blue = 3)

constexpr Channel      channel = Channel::_from_integral(2);
constexpr int          value = channel._to_integral();

constexpr const char   *name = channel._to_string();
constexpr Channel      parsed = Channel::_from_string("Red");

// All of the above are computed during compilation. The reason for the macro
// definition at the top of the file is explained on the opt-in features page.
// Basically, it makes _to_string constexpr, but slows down compilation.
//
// You can also do things such as:

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
