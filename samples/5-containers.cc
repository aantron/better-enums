// Usage with STL containers.

#include <iostream>
#include <map>
#include <vector>

#include <enum.h>

ENUM(Channel, int, Red, Green, Blue);

int main()
{
    // Vectors.
    std::vector<Channel>    vector = {Channel::Red, Channel::Green};

    vector.push_back(Channel::Red);
    vector.push_back(Channel::Blue);
    vector.push_back(Channel::Blue);
    vector.push_back(Channel::Red);

    for (Channel channel : vector)
        std::cout << channel.to_string() << " ";
    std::cout << std::endl;



    // Maps. Lack of a default constructor in the current version means that
    // std::map::operator[] usage is complicated. Insertion can still be done
    // with ::insert, and access with ::find.
    std::map<const char*, Channel>  map = {{"first", Channel::Blue}};
    map.insert({"second", Channel::Green});

    for (Channel channel : Channel::_values)
        map.insert({channel.to_string(), channel});

    bool    first = true;
    for (auto item : map) {
        if (first)
            first = false;
        else
            std::cout << ", ";

        std::cout
            << item.first
            << " -> "
            << item.second.to_string();
    }
    std::cout << std::endl;



    // As map keys.
    std::map<Channel, const char*>  descriptions =
        {{Channel::Red,   "the red channel"},
         {Channel::Green, "the green channel"},
         {Channel::Blue,  "the blue channel"}};

    for (auto item : descriptions)
        std::cout << item.second << std::endl;

    return 0;
}
