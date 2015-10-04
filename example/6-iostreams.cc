// This file was generated automatically.

// Stream operators
//
// These work almost as you'd expect. First, make sure you include iostream
// before enum.h in any translation unit in which you intend to use the
// operators:

#include <iostream>
#include <enum.h>

BETTER_ENUM(Channel, int, Red, Green, Blue)

int main()
{
    std::cout << +Channel::Red << std::endl;
    return 0;
}

// The thing to watch for is the +: without it, Channel::Red is a value of type
// Channel::_enumerated, a C++98 enum type, so writing that to cout will output
// an integer. +Channel::Red, however, is a value of type Channel, and writing
// that instead will output the string "Red".
//
// Input is also supported:
//
// Channel     channel = Channel::Blue;
// std::cin >> channel;    // Expects input such as "Green".

// Only char streams are supported for the time being.
