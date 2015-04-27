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

#define ENUM(EnumType, UnderlyingType, ...)                                    \
    _ENUM_ARRAYS(EnumType, UnderlyingType, __VA_ARGS__);                       \
                                                                               \
    class EnumType : public _enum::_Internal<EnumType> {                       \
      protected:                                                               \
        using _Super = _enum::_Internal<EnumType>;                             \
                                                                               \
      public:                                                                  \
        static constexpr _Value     _min = (_Value)_values[_minIndex];         \
        static constexpr _Value     _max = (_Value)_values[_maxIndex];         \
                                                                               \
        static constexpr size_t     _span = _max - _min + 1;                   \
                                                                               \
        static ValueIterable _values() { return _Super::values(); }            \
        static NameIterable _names() { return _Super::names(); }               \
                                                                               \
        const char* to_string() const { return desc(*this); }                  \
        static EnumType _from_string(const char *name)                         \
            { return _Super::find(name); }                                     \
        static EnumType _from_string_nocase(const char *name)                  \
            { return _Super::caseFind(name); }                                 \
                                                                               \
        Underlying to_int() const { return _value; }                           \
        static EnumType _from_int(Underlying value)                            \
            { return EnumType(value); }                                        \
        static EnumType _from_int_unchecked(Underlying value)                  \
            { return EnumType(value); }                                        \
                                                                               \
        template <typename IntegralType>                                       \
        static bool _is_valid(IntegralType value)                              \
            { return _Super::valid(value); }                                   \
        static bool _is_valid(const char *name)                                \
            { return _Super::valid(name); }                                    \
        static bool _is_valid_nocase(const char *name)                         \
            { return _Super::caseValid(name); }                                \
                                                                               \
        EnumType() = delete;                                                   \
        EnumType(_Value value) : _value(value) { }                             \
        template <typename IntegralType>                                       \
        explicit EnumType(IntegralType value,                                  \
                          typename                                             \
                              std::enable_if<                                  \
                                  std::is_integral<IntegralType>::value>       \
                                      ::type *dummy = nullptr) : _value(value) \
            { }                                                                \
                                                                               \
        template <typename IntegralType>                                       \
        EnumType& operator =(IntegralType value)                               \
            { *this = EnumType(value); return *this; }                         \
                                                                               \
        operator _Value () const { return (_Value)_value; }                    \
        Underlying toUnderlying() const { return (Underlying)_value; }         \
                                                                               \
      protected:                                                               \
        Underlying                  _value;                                    \
                                                                               \
        friend _Super;                                                         \
        friend ValueIterable;                                                  \
    };                                                                         \
                                                                               \
    static_assert(sizeof(EnumType) == sizeof(UnderlyingType),                  \
                  "internal error: enum type does not have same size as its "  \
                  "underlying type");                                          \
    static_assert(alignof(EnumType) == alignof(UnderlyingType),                \
                  "internal error: enum type does not have same alignment "    \
                  "requirement as its underlying type");
