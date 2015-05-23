// Iteration over all constants.

#include <iostream>
#include <enum.h>

ENUM(Channel, int, Red = 3, Green = 4, Blue = 0)

int main()
{
    // Listing declared values. Output is 3 4 0.
    for (Channel channel : Channel::_values)
        std::cout << channel._to_integral() << " ";
    std::cout << std::endl;

    // Listing declared names. Output is Red Green Blue.
    for (const char *name : Channel::_names)
        std::cout << name << " ";
    std::cout << std::endl;



    // Direct iterator usage. Output is Red.
    std::cout
        << "first (using iterator): "
        << *Channel::_names.begin()
        << std::endl;

    return 0;
}
