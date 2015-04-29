/// @file Enum.h
/// Enum type generator.
///
/// @todo Provide type name as a string.



#pragma once

#include "EnumInternal.h"



// TODO toUnderlying can probably be constexpr.
// TODO Consider using a traits type instead of prefixing static members with an
// underscore.
// TODO Make appropriate changes in naming in EnumInternal.h. Most especially,
// remove any names that may conflict with value constant names.
// TODO Make the default cast checked.
// TODO Create explicit members that do everything the constructors and
// operators do, and define the operators in terms of those.
// TODO Remove implicit conversion to underlying type.
// TODO Rename Underlying so it doesn't clash with any value names.
// TODO _first, _last, _count.
// TODO Try to make names and values into values instead of functions.
// TODO Move the member value into the base class and define most functions
// there.
// TODO Make sure to cast to the underlying type in to_int.

#define ENUM(EnumType, UnderlyingType, ...)                                    \
    _ENUM_ARRAYS(EnumType, UnderlyingType, __VA_ARGS__);                       \
                                                                               \
    class EnumType : public _enum::_Implementation<EnumType> {                 \
        using _Super = _enum::_Implementation<EnumType>;                       \
        using _Super::_Super;                                                  \
        friend _Super;                                                         \
        friend _Super::_ValueIterable;                                         \
    };                                                                         \
                                                                               \
    _ENUM_STATIC_DEFINITIONS(EnumType);
