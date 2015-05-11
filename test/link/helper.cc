#include <iostream>
#include "shared.h"

void print(Channel channel)
{
    std::cout << Channel::_name << "::" << channel.to_string() << std::endl;
}
