// This file was generated automatically.

// Iteration
//
// Better Enums makes it easy to iterate over the values you have declared. For
// example, this:

#include <iostream>
#include <enum.h>

BETTER_ENUM(Channel, int, Red, Green = 2, Blue)

int main()
{

    for (size_t index = 0; index < Channel::_size(); ++index) {
        Channel     channel = Channel::_values()[index];
        std::cout << channel._to_integral() << " ";
    }
    std::cout << std::endl;

// will print "0 2 3". And this:

    for (size_t index = 0; index < Channel::_size(); ++index) {
        const char  *name = Channel::_names()[index];
        std::cout << name << " ";
    }
    std::cout << std::endl;

// will print "Red Green Blue".

// If you are using C++11, you can have much nicer syntax:
//
//     for (Channel channel : Channel::_values())
//         std::cout << channel._to_integral() << " ";
//     std::cout << std::endl;
//
//     for (const char *name : Channel::_names())
//         std::cout << name << " ";
//     std::cout << std::endl;


    return 0;
}
