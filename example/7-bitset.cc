// Usage with std::bitset.

#include <bitset>
#include <iostream>
#include <enum.h>

// Computes the maximum value of an enum at compile time.
template <typename Enum>
constexpr Enum maximum(Enum accumulator = Enum::_values()[0], size_t index = 1)
{
    return
        index >= Enum::_size ? accumulator :
        Enum::_values()[index] > accumulator ?
            maximum(Enum::_values()[index], index + 1) :
            maximum(accumulator, index + 1);
}

ENUM(Channel, int, Red, Green, Blue)

int main()
{
    using ChannelSet = std::bitset<maximum<Channel>()._to_integral() + 1>;

    ChannelSet  red_only;
    red_only.set(Channel::Red);

    ChannelSet  blue_only;
    blue_only.set(Channel::Blue);

    ChannelSet  red_and_blue = red_only | blue_only;

    for (Channel channel : Channel::_values()) {
        std::cout
            << channel._to_string()
            << " bit is set to "
            << red_and_blue[channel._to_integral()]
            << std::endl;
    }

    if (red_and_blue[Channel::Green])
        std::cout << "bit set contains Green" << std::endl;

    return 0;
}
