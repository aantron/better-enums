// Range properties and iteration over all constants.

#include <iostream>
#include <enum.h>

ENUM(Channel, int, Red = 3, Green = 4, Blue = 0);

int main()
{
    // Static range properties.
    std::cout << "first:   " << (+Channel::_first).to_string() << std::endl;
    std::cout << "last:    " << (+Channel::_last).to_string()  << std::endl;
    std::cout << "minimum: " << (+Channel::_min).to_string()   << std::endl;
    std::cout << "maximum: " << (+Channel::_max).to_string()   << std::endl;
    std::cout << "count:   " << Channel::_size << std::endl;
    std::cout << "span:    " << Channel::_span << std::endl;



    // Listing declared values.
    for (Channel channel : Channel::_values)
        std::cout << channel.to_integral() << " ";
    std::cout << std::endl;

    // Listing declared names.
    for (const char *name : Channel::_names)
        std::cout << name << " ";
    std::cout << std::endl;



    // Direct iterator usage.
    std::cout
        << "first (using iterator): "
        << *Channel::_names.begin()
        << std::endl;

    return 0;
}
