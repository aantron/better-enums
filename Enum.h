/// @file Enum.h
/// Enum type generator.
///
/// @todo Provide type name as a string.



#pragma once

#include "EnumInternal.h"



// TODO Consider using a traits type instead of prefixing static members with an
// underscore.
// TODO Make appropriate changes in naming in EnumInternal.h. Most especially,
// remove any names that may conflict with value constant names.
// TODO Make the default cast checked.
// TODO Create explicit members that do everything the constructors and
// operators do, and define the operators in terms of those.
// TODO _first, _last, _count.
// TODO Try to make names and values into values instead of functions.

#define ENUM(EnumType, UnderlyingType, ...)                                    \
    _ENUM_TAG_DECLARATION(EnumType);                                           \
    _ENUM_ARRAYS(EnumType, UnderlyingType, _ENUM_TAG(EnumType), __VA_ARGS__);  \
    using EnumType = _enum::_Enum<_enum::_ENUM_TAG(EnumType)>;                 \
    _ENUM_STATIC_DEFINITIONS(EnumType);
