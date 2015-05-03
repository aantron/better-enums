/// @file Enum.h
/// Enum type generator.



#pragma once

#include "EnumInternal.h"



// TODO Consider using a traits type instead of prefixing static members with an
// underscore.

#define ENUM(EnumType, UnderlyingType, ...)                                    \
    _ENUM_TAG_DECLARATION(EnumType);                                           \
    _ENUM_ARRAYS(EnumType, UnderlyingType, _ENUM_TAG(EnumType), __VA_ARGS__);  \
    using EnumType = _enum::_Enum<_enum::_ENUM_TAG(EnumType)>;                 \
    _ENUM_STATIC_DEFINITIONS(EnumType, _ENUM_TAG(EnumType));
