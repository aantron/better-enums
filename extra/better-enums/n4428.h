// This file is part of Better Enums, released under the BSD 2-clause license.
// See doc/LICENSE for details, or visit http://github.com/aantron/better-enums.

// This file provides an implementation of the enum reflection interface
// proposed in
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4428.pdf
// on top of Better Enums.

// See further discussion and a demonstration of usage at
// example/107-c++17-reflection.cc, or visit:
//     http://aantron.github.io/better-enums/demo/C++17ReflectionProposal.html

#pragma once

#ifndef BETTER_ENUMS_N4428_H
#define BETTER_ENUMS_N4428_H



namespace std {

template <typename Enum>
struct enum_traits {
    struct enumerators {
        constexpr static const size_t   size = Enum::_size();

        template <size_t Index>
        struct get {
            constexpr static Enum       value = Enum::_values()[Index];
            constexpr static const char *identifier = Enum::_names()[Index];
        };

        // The above declarations implement N4428 (except for const char*
        // instead of string_literal). The alternative get below is needed for
        // Better Enums that weren't generated with compile-time name trimming,
        // i.e. without BETTER_ENUMS_CONSTEXPR_TO_STRING declared and not
        // through the SLOW_ENUM macro. That is currently the default for
        // Better Enums, since compile-time name trimming is pretty slow, so you
        // would want to use get_alt instead of get.
        template <size_t Index>
        struct get_alt {
            constexpr static Enum       value = Enum::_values()[Index];
            static const char* identifier() { return Enum::_names()[Index]; };
        };
    };
};

}



#endif // #ifndef BETTER_ENUMS_N4428_H
