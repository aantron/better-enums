// Range properties and iteration over all constants.

#include <iostream>
#include <enum.h>

ENUM(Channel, int, Red = 3, Green = 4, Blue = 0);

int main()
{
    // Static range properties.
    std::cout << "first:   " <<
        enum_::to_string(enum_::traits<Channel>::first) << std::endl;
    std::cout << "last:    " <<
        enum_::to_string(enum_::traits<Channel>::last)  << std::endl;
    std::cout << "minimum: " <<
        enum_::to_string(enum_::traits<Channel>::min)   << std::endl;
    std::cout << "maximum: " <<
        enum_::to_string(enum_::traits<Channel>::max)   << std::endl;
    std::cout << "count:   " << enum_::traits<Channel>::size << std::endl;
    std::cout << "span:    " << enum_::traits<Channel>::span << std::endl;



    // Listing declared values.
    for (Channel channel : enum_::traits<Channel>::values)
        std::cout << enum_::to_integral(channel) << " ";
    std::cout << std::endl;

    // Listing declared names.
    for (const char *name : enum_::traits<Channel>::names)
        std::cout << name << " ";
    std::cout << std::endl;



    // Direct iterator usage.
    std::cout
        << "first (using iterator): "
        << *enum_::traits<Channel>::names.begin()
        << std::endl;

    return 0;
}
