// Usage with std::bitset.

#include <bitset>
#include <iostream>
#include <enum.h>

ENUM(Channel, int, Red, Green, Blue);

int main()
{
    using ChannelSet = std::bitset<Channel::_span>;

    ChannelSet  red_only;
    red_only.set(Channel::Red);

    ChannelSet  blue_only;
    blue_only.set(Channel::Blue);

    ChannelSet  red_and_blue = red_only | blue_only;

    for (Channel channel : Channel::_values) {
        std::cout
            << channel.to_string()
            << " bit is set to "
            << red_and_blue[channel]
            << std::endl;
    }

    if (red_and_blue[Channel::Green])
        std::cout << "bit set contains Green" << std::endl;

    return 0;
}
