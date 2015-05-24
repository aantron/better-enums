// Switch case exhaustiveness checking.

#include <iostream>
#include <enum.h>

ENUM(Channel, int, Red, Green, Blue)

void respond_to_channel(Channel channel)
{
    // Try adding an extra case or removing one. Your compiler should issue a
    // warning.
    switch (channel) {
        case Channel::Red:
            std::cout << "red channel" << std::endl;
            break;

        case Channel::Green:
            std::cout << "green channel" << std::endl;
            break;

        case Channel::Blue:
            std::cout << "blue channel" << std::endl;
            break;

        // A redundant case.
        // case 3:
        //     break;
    }
}

int main()
{
    respond_to_channel(Channel::Red);
    respond_to_channel(Channel::Blue);
    respond_to_channel(Channel::Green);

    return 0;
}
