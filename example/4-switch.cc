// This file was generated automatically.

// Safe switch
//
// A Better Enum can be used directly in a switch statement:

#include <iostream>
#include <enum.h>

BETTER_ENUM(Channel, int, Red, Green, Blue)

int main()
{
    Channel     channel = Channel::Green;
    int         n;

    switch (channel) {
        case Channel::Red:   n = 13; break;
        case Channel::Green: n = 37; break;
        case Channel::Blue:  n = 42; break;
    }

// If you miss a case or add a redundant one, your compiler should be able to
// give you a warning - try it!


    std::cout << n << std::endl;
    return 0;
}
