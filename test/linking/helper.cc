#include <iostream>
#include "shared.h"

void print(Channel channel)
{
    std::cout << Channel::_name() << "::" << channel._to_string() << std::endl;
    std::cout << Channel::_size() << std::endl;
}
