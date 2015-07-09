// This file is part of Better Enums, released under the BSD 2-clause license.
// See doc/LICENSE for details, or visit http://github.com/aantron/better-enums.

// This file provides an implementation of the enum reflection interface
// proposed in
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4428.pdf
// over Better Enums.

// See further discussion and a demonstration of usage at
// example/107-c++17-reflection.cc, or visit:
//     http://aantron.github.io/better-enums/demo/C++17Reflection.html

#pragma once

#ifndef BETTER_ENUMS__N4428_H
#define BETTER_ENUMS__N4428_H



namespace std {

template <typename Enum>
struct enum_traits {
    struct enumerators {
        constexpr static const size_t   size = Enum::_size();

        template <size_t Index>
        struct get {
            constexpr static Enum       value = Enum::_values()[Index];

            // In the proposal, this is a constexpr variable of type
            // string_literal. It is possible to declare "identifier" that way
            // with Better Enums, but only for enums that have compile-time name
            // trimming enabled. Since compile-time name trimming currently has
            // a severe performance impact, and is disabled by default, I chose
            // to implement "identifier" as a function.
            static const char* identifier() { return Enum::_names()[Index]; };
        };
    };
};

}



#endif // #ifndef BETTER_ENUMS__N4428_H
