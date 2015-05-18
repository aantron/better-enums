// Compile-time iteration. This example generates an approximation of enum
// declarations (without explicit "="" settings) at run time. The storage space
// for this is reserved at compile time, however.

#include <cassert>
#include <cstring>
#include <iostream>
#include <enum.h>

ENUM(Channel, int, Red, Green, Blue);
ENUM(Depth, int, TrueColor, HighColor);

// Computes the length of a string.
constexpr size_t string_length(const char *s, size_t index = 0)
{
    return s[index] == '\0' ? index : string_length(s, index + 1);
}

// Runs over all the constants in an enum and adds up the lengths of their
// names.
template <typename Enum>
constexpr size_t total_names_length(size_t accumulator = 0, size_t index = 0)
{
    return
        index == Enum::_size ? accumulator :
        total_names_length<Enum>
            (accumulator + string_length(Enum::_names[index]), index + 1);
}

// Computes the total length of an ENUM declaration, assuming the type is int.
// The summands correspond to each of the tokens and spaces (i.e., "ENUM", "(",
// etc.). (Enum::_size - 1) * 2 is added to account for each comma and space
// following each constant name, except for the last one. The final 1 is added
// to account for the null terminator.
template <typename Enum>
constexpr size_t declaration_length()
{
    return
        4 + 1 + string_length(Enum::_name) + 1 + 1 + 3 + 1 + 1 +
        total_names_length<Enum>() + (Enum::_size - 1) * 2 + 1 + 1 + 1;
}

// Formats the declaration into space already reserved.
template <typename Enum>
void format_declaration(char *storage)
{
    std::strcat(storage, "ENUM(");
    std::strcat(storage, Enum::_name);
    std::strcat(storage, ", int, ");

    for (auto name_iterator = Enum::_names.begin();
         name_iterator < Enum::_names.end() - 1; ++name_iterator) {

        std::strcat(storage, *name_iterator);
        std::strcat(storage, ", ");
    }
    std::strcat(storage, Enum::_names[Enum::_size - 1]);

    std::strcat(storage, ");");

    assert(std::strlen(storage) == declaration_length<Enum>() - 1);
}

// Reserve space for the formatted declaration of each enum. These buffers
// should be zeroed at load time or during code generation, so, semantically,
// they contain the empty string.
char    channel_declaration[declaration_length<Channel>()];
char    depth_declaration[declaration_length<Depth>()];



int main()
{
    format_declaration<Channel>(channel_declaration);
    std::cout << channel_declaration << std::endl;

    format_declaration<Depth>(depth_declaration);
    std::cout << depth_declaration << std::endl;

    return 0;
}
