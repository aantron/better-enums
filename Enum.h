/// @file Enum.h
/// Enum type generator.
///
/// @todo Provide type name as a string.



#pragma once

#include "EnumInternal.h"



// TODO (DOC) Link to the main enum documentation from the macro documentation,
// or paste it here?
// TODO (DOC) Improve the readability and formatting of enum documentation.
// TODO (DOC) Refer to detailed documentation of internals in EnumInternal.h.
// TODO Document why it's okay to convert the value span to an unsigned integer.
// TODO `size()` is only for compatibility with `BETTER_ENUM`.
// TODO toUnderlying can probably be constexpr.
// TODO If type name is added to the class, it would be useful in pyatl.

#define ENUM(EnumType, UnderlyingType, ...)                                    \
    _ENUM_ARRAYS(EnumType, UnderlyingType, __VA_ARGS__);                       \
                                                                               \
    class EnumType : public _enum::_Internal<EnumType> {                       \
      protected:                                                               \
        using _Super = _enum::_Internal<EnumType>;                             \
                                                                               \
      public:                                                                  \
        using Enum = _Value;                                                   \
                                                                               \
        static constexpr _Value     bad = (_Value)_values[_badIndex];          \
        static constexpr _Value     def = (_Value)_values[_defIndex];          \
        static constexpr _Value     min = (_Value)_values[_minIndex];          \
        static constexpr _Value     max = (_Value)_values[_maxIndex];          \
                                                                               \
        static constexpr size_t     span = max - min + 1;                      \
                                                                               \
        static constexpr size_t size() { return _size; }                       \
                                                                               \
        static constexpr _Value     MaxValid = max;                            \
        static constexpr _Value     MinValid = min;                            \
                                                                               \
        static ValueIterable values() { return _Super::values(); }             \
        static ValueIterable allValues() { return _Super::allValues(); }       \
        static NameIterable names() { return _Super::names(); }                \
        static NameIterable allNames() { return _Super::allNames(); }          \
                                                                               \
        const char* desc() const { return desc(*this); }                       \
        const char* descE() const { return descE(*this); }                     \
                                                                               \
        static const char* desc(EnumType value) { return _Super::desc(value); }\
        static const char* descE(EnumType value)                               \
            { return _Super::descE(value); }                                   \
                                                                               \
        static EnumType find(const char *name) { return _Super::find(name); }  \
        static EnumType findE(const char *name) { return _Super::findE(name); }\
                                                                               \
        static EnumType caseFind(const char *name)                             \
            { return _Super::caseFind(name); }                                 \
        static EnumType caseFindE(const char *name)                            \
            { return _Super::caseFindE(name); }                                \
                                                                               \
        bool valid() const { return valid(this->toUnderlying()); };            \
                                                                               \
        template <typename IntegralType>                                       \
        static bool valid(IntegralType value) { return _Super::valid(value); } \
        static bool valid(const char *name) { return _Super::valid(name); }    \
        static bool caseValid(const char *name)                                \
            { return _Super::caseValid(name); }                                \
                                                                               \
        EnumType() : _value(def) { }                                           \
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
