// This file is part of Better Enums, released under the BSD 2-clause license.
// See LICENSE for details, or visit http://github.com/aantron/better-enums.

#pragma once

#ifndef _BETTER_ENUMS_ENUM_H_
#define _BETTER_ENUMS_ENUM_H_



#include <cstddef>
#include <cstring>
#include <stdexcept>



#ifdef BETTER_ENUMS_CONSTEXPR
#   define _ENUM_HAVE_CONSTEXPR
#else
#   ifdef __GNUC__
#       ifdef __clang__
#           if __has_feature(cxx_constexpr)
#               define _ENUM_HAVE_CONSTEXPR
#           endif
#       else
#           if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#               if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#                   define _ENUM_HAVE_CONSTEXPR
#               endif
#           endif
#       endif
#   endif
#endif

#ifdef BETTER_ENUMS_NO_CONSTEXPR
#   if defined(_ENUM_HAVE_CONSTEXPR)
#       undef _ENUM_HAVE_CONSTEXPR
#   endif
#endif

#ifdef _ENUM_HAVE_CONSTEXPR
#   define _ENUM_CONSTEXPR      constexpr
#   define _ENUM_NULLPTR        nullptr
#else
#   define _ENUM_CONSTEXPR
#   define _ENUM_NULLPTR        NULL
#endif

#ifndef __GNUC__
#   define strcasecmp           stricmp
#endif



#ifdef BETTER_ENUMS_MACRO_FILE
#   include BETTER_ENUMS_MACRO_FILE
#else

#define _ENUM_PP_MAP(macro, data, ...) \
    _ENUM_ID(_ENUM_A(_ENUM_PP_MAP_VAR_COUNT, _ENUM_PP_COUNT(__VA_ARGS__)) \
        (macro, data, __VA_ARGS__))

#define _ENUM_PP_MAP_VAR_COUNT(count) _ENUM_M ## count

#define _ENUM_A(macro, ...) _ENUM_ID(macro(__VA_ARGS__))

#define _ENUM_ID(x) x

#define _ENUM_M1(m, d, x) m(d,0,x)
#define _ENUM_M2(m,d,x,...) m(d,1,x) _ENUM_ID(_ENUM_M1(m,d,__VA_ARGS__))
#define _ENUM_M3(m,d,x,...) m(d,2,x) _ENUM_ID(_ENUM_M2(m,d,__VA_ARGS__))
#define _ENUM_M4(m,d,x,...) m(d,3,x) _ENUM_ID(_ENUM_M3(m,d,__VA_ARGS__))
#define _ENUM_M5(m,d,x,...) m(d,4,x) _ENUM_ID(_ENUM_M4(m,d,__VA_ARGS__))
#define _ENUM_M6(m,d,x,...) m(d,5,x) _ENUM_ID(_ENUM_M5(m,d,__VA_ARGS__))
#define _ENUM_M7(m,d,x,...) m(d,6,x) _ENUM_ID(_ENUM_M6(m,d,__VA_ARGS__))
#define _ENUM_M8(m,d,x,...) m(d,7,x) _ENUM_ID(_ENUM_M7(m,d,__VA_ARGS__))
#define _ENUM_M9(m,d,x,...) m(d,8,x) _ENUM_ID(_ENUM_M8(m,d,__VA_ARGS__))
#define _ENUM_M10(m,d,x,...) m(d,9,x) _ENUM_ID(_ENUM_M9(m,d,__VA_ARGS__))
#define _ENUM_M11(m,d,x,...) m(d,10,x) _ENUM_ID(_ENUM_M10(m,d,__VA_ARGS__))
#define _ENUM_M12(m,d,x,...) m(d,11,x) _ENUM_ID(_ENUM_M11(m,d,__VA_ARGS__))
#define _ENUM_M13(m,d,x,...) m(d,12,x) _ENUM_ID(_ENUM_M12(m,d,__VA_ARGS__))
#define _ENUM_M14(m,d,x,...) m(d,13,x) _ENUM_ID(_ENUM_M13(m,d,__VA_ARGS__))
#define _ENUM_M15(m,d,x,...) m(d,14,x) _ENUM_ID(_ENUM_M14(m,d,__VA_ARGS__))
#define _ENUM_M16(m,d,x,...) m(d,15,x) _ENUM_ID(_ENUM_M15(m,d,__VA_ARGS__))
#define _ENUM_M17(m,d,x,...) m(d,16,x) _ENUM_ID(_ENUM_M16(m,d,__VA_ARGS__))
#define _ENUM_M18(m,d,x,...) m(d,17,x) _ENUM_ID(_ENUM_M17(m,d,__VA_ARGS__))
#define _ENUM_M19(m,d,x,...) m(d,18,x) _ENUM_ID(_ENUM_M18(m,d,__VA_ARGS__))
#define _ENUM_M20(m,d,x,...) m(d,19,x) _ENUM_ID(_ENUM_M19(m,d,__VA_ARGS__))
#define _ENUM_M21(m,d,x,...) m(d,20,x) _ENUM_ID(_ENUM_M20(m,d,__VA_ARGS__))
#define _ENUM_M22(m,d,x,...) m(d,21,x) _ENUM_ID(_ENUM_M21(m,d,__VA_ARGS__))
#define _ENUM_M23(m,d,x,...) m(d,22,x) _ENUM_ID(_ENUM_M22(m,d,__VA_ARGS__))
#define _ENUM_M24(m,d,x,...) m(d,23,x) _ENUM_ID(_ENUM_M23(m,d,__VA_ARGS__))
#define _ENUM_M25(m,d,x,...) m(d,24,x) _ENUM_ID(_ENUM_M24(m,d,__VA_ARGS__))
#define _ENUM_M26(m,d,x,...) m(d,25,x) _ENUM_ID(_ENUM_M25(m,d,__VA_ARGS__))
#define _ENUM_M27(m,d,x,...) m(d,26,x) _ENUM_ID(_ENUM_M26(m,d,__VA_ARGS__))
#define _ENUM_M28(m,d,x,...) m(d,27,x) _ENUM_ID(_ENUM_M27(m,d,__VA_ARGS__))
#define _ENUM_M29(m,d,x,...) m(d,28,x) _ENUM_ID(_ENUM_M28(m,d,__VA_ARGS__))
#define _ENUM_M30(m,d,x,...) m(d,29,x) _ENUM_ID(_ENUM_M29(m,d,__VA_ARGS__))
#define _ENUM_M31(m,d,x,...) m(d,30,x) _ENUM_ID(_ENUM_M30(m,d,__VA_ARGS__))
#define _ENUM_M32(m,d,x,...) m(d,31,x) _ENUM_ID(_ENUM_M31(m,d,__VA_ARGS__))
#define _ENUM_M33(m,d,x,...) m(d,32,x) _ENUM_ID(_ENUM_M32(m,d,__VA_ARGS__))
#define _ENUM_M34(m,d,x,...) m(d,33,x) _ENUM_ID(_ENUM_M33(m,d,__VA_ARGS__))
#define _ENUM_M35(m,d,x,...) m(d,34,x) _ENUM_ID(_ENUM_M34(m,d,__VA_ARGS__))
#define _ENUM_M36(m,d,x,...) m(d,35,x) _ENUM_ID(_ENUM_M35(m,d,__VA_ARGS__))
#define _ENUM_M37(m,d,x,...) m(d,36,x) _ENUM_ID(_ENUM_M36(m,d,__VA_ARGS__))
#define _ENUM_M38(m,d,x,...) m(d,37,x) _ENUM_ID(_ENUM_M37(m,d,__VA_ARGS__))
#define _ENUM_M39(m,d,x,...) m(d,38,x) _ENUM_ID(_ENUM_M38(m,d,__VA_ARGS__))
#define _ENUM_M40(m,d,x,...) m(d,39,x) _ENUM_ID(_ENUM_M39(m,d,__VA_ARGS__))
#define _ENUM_M41(m,d,x,...) m(d,40,x) _ENUM_ID(_ENUM_M40(m,d,__VA_ARGS__))
#define _ENUM_M42(m,d,x,...) m(d,41,x) _ENUM_ID(_ENUM_M41(m,d,__VA_ARGS__))
#define _ENUM_M43(m,d,x,...) m(d,42,x) _ENUM_ID(_ENUM_M42(m,d,__VA_ARGS__))
#define _ENUM_M44(m,d,x,...) m(d,43,x) _ENUM_ID(_ENUM_M43(m,d,__VA_ARGS__))
#define _ENUM_M45(m,d,x,...) m(d,44,x) _ENUM_ID(_ENUM_M44(m,d,__VA_ARGS__))
#define _ENUM_M46(m,d,x,...) m(d,45,x) _ENUM_ID(_ENUM_M45(m,d,__VA_ARGS__))
#define _ENUM_M47(m,d,x,...) m(d,46,x) _ENUM_ID(_ENUM_M46(m,d,__VA_ARGS__))
#define _ENUM_M48(m,d,x,...) m(d,47,x) _ENUM_ID(_ENUM_M47(m,d,__VA_ARGS__))
#define _ENUM_M49(m,d,x,...) m(d,48,x) _ENUM_ID(_ENUM_M48(m,d,__VA_ARGS__))
#define _ENUM_M50(m,d,x,...) m(d,49,x) _ENUM_ID(_ENUM_M49(m,d,__VA_ARGS__))
#define _ENUM_M51(m,d,x,...) m(d,50,x) _ENUM_ID(_ENUM_M50(m,d,__VA_ARGS__))
#define _ENUM_M52(m,d,x,...) m(d,51,x) _ENUM_ID(_ENUM_M51(m,d,__VA_ARGS__))
#define _ENUM_M53(m,d,x,...) m(d,52,x) _ENUM_ID(_ENUM_M52(m,d,__VA_ARGS__))
#define _ENUM_M54(m,d,x,...) m(d,53,x) _ENUM_ID(_ENUM_M53(m,d,__VA_ARGS__))
#define _ENUM_M55(m,d,x,...) m(d,54,x) _ENUM_ID(_ENUM_M54(m,d,__VA_ARGS__))
#define _ENUM_M56(m,d,x,...) m(d,55,x) _ENUM_ID(_ENUM_M55(m,d,__VA_ARGS__))
#define _ENUM_M57(m,d,x,...) m(d,56,x) _ENUM_ID(_ENUM_M56(m,d,__VA_ARGS__))
#define _ENUM_M58(m,d,x,...) m(d,57,x) _ENUM_ID(_ENUM_M57(m,d,__VA_ARGS__))
#define _ENUM_M59(m,d,x,...) m(d,58,x) _ENUM_ID(_ENUM_M58(m,d,__VA_ARGS__))
#define _ENUM_M60(m,d,x,...) m(d,59,x) _ENUM_ID(_ENUM_M59(m,d,__VA_ARGS__))
#define _ENUM_M61(m,d,x,...) m(d,60,x) _ENUM_ID(_ENUM_M60(m,d,__VA_ARGS__))
#define _ENUM_M62(m,d,x,...) m(d,61,x) _ENUM_ID(_ENUM_M61(m,d,__VA_ARGS__))
#define _ENUM_M63(m,d,x,...) m(d,62,x) _ENUM_ID(_ENUM_M62(m,d,__VA_ARGS__))
#define _ENUM_M64(m,d,x,...) m(d,63,x) _ENUM_ID(_ENUM_M63(m,d,__VA_ARGS__))

#define _ENUM_PP_COUNT_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, \
    _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
    _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, \
    _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, \
    _58, _59, _60, _61, _62, _63, _64, count, ...) count

#define _ENUM_PP_COUNT(...) _ENUM_ID(_ENUM_PP_COUNT_IMPL(__VA_ARGS__, 64, 63,  \
    62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44,\
    43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25,\
    24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, \
    4, 3, 2, 1))

#define _ENUM_ITERATE(X, f, l) X(f, l, 0) X(f, l, 1) X(f, l, 2) X(f, l, 3)     \
    X(f, l, 4) X(f, l, 5) X(f, l, 6) X(f, l, 7) X(f, l, 8) X(f, l, 9)          \
    X(f, l, 10) X(f, l, 11) X(f, l, 12) X(f, l, 13) X(f, l, 14) X(f, l, 15)    \
    X(f, l, 16) X(f, l, 17) X(f, l, 18) X(f, l, 19) X(f, l, 20) X(f, l, 21)    \
    X(f, l, 22) X(f, l, 23)

#endif // #ifdef BETTER_ENUMS_MACRO_FILE



#define _ENUM_EAT_ASSIGN_SINGLE(EnumType, index, expression)                   \
    ((better_enums::_eat_assign<EnumType>)EnumType::expression),

#define _ENUM_EAT_ASSIGN(EnumType, ...)                                        \
    _ENUM_ID(_ENUM_PP_MAP(_ENUM_EAT_ASSIGN_SINGLE, EnumType, __VA_ARGS__))



#define _ENUM_NS(EnumType)      better_enums::_data_ ## EnumType
#define _ENUM_NAME_ENDERS       "= \t\n"



namespace better_enums {

template <typename T>
_ENUM_CONSTEXPR inline T _default()
{
    return (typename T::_enumerated)0;
}

template <>
_ENUM_CONSTEXPR inline const char* _default<const char*>()
{
    return _ENUM_NULLPTR;
}

template <>
_ENUM_CONSTEXPR inline std::size_t _default<std::size_t>()
{
    return 0;
}

template <typename T>
struct optional {
    _ENUM_CONSTEXPR optional() : _valid(false), _value(_default<T>()) { }
    _ENUM_CONSTEXPR optional(T v) : _valid(true), _value(v) { }

    _ENUM_CONSTEXPR const T& operator *() const { return _value; }
    _ENUM_CONSTEXPR const T* operator ->() const { return &_value; }

    _ENUM_CONSTEXPR operator bool() const { return _valid; }

    _ENUM_CONSTEXPR const T& value() const { return _value; }

  private:
    bool    _valid;
    T       _value;
};

template <typename CastTo, typename Element>
_ENUM_CONSTEXPR static optional<CastTo>
_map_index(const Element *array, optional<std::size_t> index)
{
    return index ? (CastTo)array[*index] : optional<CastTo>();
}

template <typename T>
_ENUM_CONSTEXPR static T _or_throw(optional<T> maybe, const char *message)
{
    return maybe ? *maybe : throw std::runtime_error(message);
}



template <typename T, typename U>
_ENUM_CONSTEXPR U continue_with(T ignored, U value) { return value; }



template <typename EnumType>
struct _eat_assign {
    explicit _ENUM_CONSTEXPR _eat_assign(EnumType value) : _value(value) { }
    template <typename Any>
    _ENUM_CONSTEXPR const _eat_assign& operator =(Any dummy) const
        { return *this; }
    _ENUM_CONSTEXPR operator EnumType () const { return _value; }

  private:
    EnumType    _value;
};



template <typename Element>
struct _Iterable {
    typedef const Element*  iterator;

    _ENUM_CONSTEXPR iterator begin() const { return iterator(_array); }
    _ENUM_CONSTEXPR iterator end() const { return iterator(_array + _size); }
    _ENUM_CONSTEXPR std::size_t size() const { return _size; }
    _ENUM_CONSTEXPR const Element& operator [](std::size_t index) const
        { return _array[index]; }

    _ENUM_CONSTEXPR _Iterable(const Element *array, std::size_t s) :
        _array(array), _size(s) { }

  private:
    const Element * const   _array;
    const std::size_t       _size;
};



_ENUM_CONSTEXPR inline bool _endsName(char c, std::size_t index = 0)
{
    return
        c == _ENUM_NAME_ENDERS[index] ? true  :
        _ENUM_NAME_ENDERS[index] == '\0' ? false :
        _endsName(c, index + 1);
}

_ENUM_CONSTEXPR inline bool _hasExplicitValue(const char *s,
                                              std::size_t index = 0)
{
    return
        s[index] == '\0' ? false :
        s[index] == '=' ? true :
        _hasExplicitValue(s, index + 1);
}

_ENUM_CONSTEXPR inline std::size_t _constantLength(const char *s,
                                                   std::size_t index = 0)
{
    return _endsName(s[index]) ? index : _constantLength(s, index + 1);
}

_ENUM_CONSTEXPR inline char _select(const char *from, std::size_t from_length,
                                    std::size_t index)
{
    return index >= from_length ? '\0' : from[index];
}

_ENUM_CONSTEXPR inline char _toLowercaseAscii(char c)
{
    return c >= 0x41 && c <= 0x5A ? (char)(c + 0x20) : c;
}

_ENUM_CONSTEXPR inline bool _namesMatch(const char *stringizedName,
                                        const char *referenceName,
                                        std::size_t index = 0)
{
    return
        _endsName(stringizedName[index]) ? referenceName[index] == '\0' :
        referenceName[index] == '\0' ? false :
        stringizedName[index] != referenceName[index] ? false :
        _namesMatch(stringizedName, referenceName, index + 1);
}

_ENUM_CONSTEXPR inline bool _namesMatchNocase(const char *stringizedName,
                                              const char *referenceName,
                                              std::size_t index = 0)
{
    return
        _endsName(stringizedName[index]) ? referenceName[index] == '\0' :
        referenceName[index] == '\0' ? false :
        _toLowercaseAscii(stringizedName[index]) !=
            _toLowercaseAscii(referenceName[index]) ? false :
        _namesMatchNocase(stringizedName, referenceName, index + 1);
}

inline void _trim_names(const char * const *raw_names,
                        const char **trimmed_names, std::size_t count)
{
    for (std::size_t index = 0; index < count; ++index) {
        std::size_t length = std::strcspn(raw_names[index], _ENUM_NAME_ENDERS);
        char        *trimmed = new char[length + 1];

        std::strncpy(trimmed, raw_names[index], length);
        trimmed[length] = '\0';

        trimmed_names[index] = trimmed;
    }
}

} // namespace better_enums



#ifdef _ENUM_HAVE_CONSTEXPR



#define _ENUM_SELECT_SINGLE_CHARACTER(from, from_length, index)                \
    _select(from, from_length, index),

#define _ENUM_SELECT_CHARACTERS(from, from_length)                             \
    _ENUM_ITERATE(_ENUM_SELECT_SINGLE_CHARACTER, from, from_length)



#define _ENUM_TRIM_SINGLE_STRING(ignored, index, expression)                   \
constexpr std::size_t   _length_ ## index = _constantLength(#expression);      \
constexpr const char    _trimmed_ ## index [] =                                \
    { _ENUM_SELECT_CHARACTERS(#expression, _length_ ## index) };               \
constexpr const char    *_final_ ## index =                                    \
    _hasExplicitValue(#expression) ? _trimmed_ ## index : #expression;

#define _ENUM_TRIM_STRINGS(...)                                                \
    _ENUM_ID(_ENUM_PP_MAP(_ENUM_TRIM_SINGLE_STRING, ignored, __VA_ARGS__))



#define _ENUM_REFER_TO_SINGLE_STRING(ignored, index, expression)               \
    _final_ ## index,

#define _ENUM_REFER_TO_STRINGS(...)                                            \
    _ENUM_ID(_ENUM_PP_MAP(_ENUM_REFER_TO_SINGLE_STRING, ignored, __VA_ARGS__))



#endif // #ifdef _ENUM_HAVE_CONSTEXPR



#define _ENUM_STRINGIZE_SINGLE(ignored, index, expression)      #expression,

#define _ENUM_STRINGIZE(...)                                                   \
    _ENUM_ID(_ENUM_PP_MAP(_ENUM_STRINGIZE_SINGLE, ignored, __VA_ARGS__))



#define _ENUM_TYPE(SetUnderlyingType, SwitchType, GenerateSwitchType,          \
                   GenerateStrings, ToStringConstexpr,                         \
                   DeclareInitialize, DefineInitialize, CallInitialize,        \
                   Enum, Integral, ...)                                        \
                                                                               \
namespace better_enums {                                                       \
namespace _data_ ## Enum {                                                     \
                                                                               \
_ENUM_ID(GenerateSwitchType(Integral, __VA_ARGS__))                            \
                                                                               \
}                                                                              \
}                                                                              \
                                                                               \
class Enum {                                                                   \
  private:                                                                     \
    typedef better_enums::optional<Enum>        _optional;                     \
    typedef better_enums::optional<std::size_t> _optional_index;               \
                                                                               \
  public:                                                                      \
    enum _enumerated SetUnderlyingType(Integral) { __VA_ARGS__ };              \
    typedef Integral                        _integral;                         \
                                                                               \
    _ENUM_CONSTEXPR Enum(_enumerated value) : _value(value) { }                \
                                                                               \
    _ENUM_CONSTEXPR operator SwitchType(Enum)() const                          \
    {                                                                          \
        return (SwitchType(Enum))_value;                                       \
    }                                                                          \
                                                                               \
    _ENUM_CONSTEXPR _integral _to_integral() const;                            \
    _ENUM_CONSTEXPR static Enum _from_integral(_integral value);               \
    _ENUM_CONSTEXPR static Enum _from_integral_unchecked(_integral value);     \
    _ENUM_CONSTEXPR static _optional _from_integral_nothrow(_integral value);  \
                                                                               \
    ToStringConstexpr const char* _to_string() const;                          \
    _ENUM_CONSTEXPR static Enum _from_string(const char *name);                \
    _ENUM_CONSTEXPR static _optional _from_string_nothrow(const char *name);   \
                                                                               \
    _ENUM_CONSTEXPR static Enum _from_string_nocase(const char *name);         \
    _ENUM_CONSTEXPR static _optional                                           \
    _from_string_nocase_nothrow(const char *name);                             \
                                                                               \
    _ENUM_CONSTEXPR static bool _is_valid(_integral value);                    \
    _ENUM_CONSTEXPR static bool _is_valid(const char *name);                   \
    _ENUM_CONSTEXPR static bool _is_valid_nocase(const char *name);            \
                                                                               \
    typedef better_enums::_Iterable<Enum>           _value_iterable;           \
    typedef better_enums::_Iterable<const char*>    _name_iterable;            \
                                                                               \
    typedef _value_iterable::iterator       _value_iterator;                   \
    typedef _name_iterable::iterator        _name_iterator;                    \
                                                                               \
    _ENUM_CONSTEXPR static const std::size_t _size =                           \
        _ENUM_ID(_ENUM_PP_COUNT(__VA_ARGS__));                                 \
                                                                               \
    _ENUM_CONSTEXPR static const char* _name();                                \
    _ENUM_CONSTEXPR static _value_iterable _values();                          \
    ToStringConstexpr static _name_iterable _names();                          \
                                                                               \
    _integral    _value;                                                       \
                                                                               \
  private:                                                                     \
    Enum() : _value(0) { }                                                     \
                                                                               \
    DeclareInitialize                                                          \
                                                                               \
    _ENUM_CONSTEXPR static _optional_index                                     \
    _from_int_loop(_integral value, std::size_t index = 0);                    \
    _ENUM_CONSTEXPR static _optional_index                                     \
    _from_string_loop(const char *name, std::size_t index = 0);                \
    _ENUM_CONSTEXPR static _optional_index                                     \
    _from_string_nocase_loop(const char *name, std::size_t index = 0);         \
};                                                                             \
                                                                               \
namespace better_enums {                                                       \
namespace _data_ ## Enum {                                                     \
                                                                               \
enum PutNamesInThisScopeAlso { __VA_ARGS__ };                                  \
                                                                               \
_ENUM_CONSTEXPR const Enum      value_array[] =                                \
    { _ENUM_ID(_ENUM_EAT_ASSIGN(Enum, __VA_ARGS__)) };                         \
                                                                               \
_ENUM_ID(GenerateStrings(Enum, __VA_ARGS__))                                   \
                                                                               \
}                                                                              \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline const Enum operator +(Enum::_enumerated enumerated)     \
    { return (Enum)enumerated; }                                               \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_integral Enum::_to_integral() const              \
{                                                                              \
    return _value;                                                             \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum                                                    \
Enum::_from_integral_unchecked(Enum::_integral value)                          \
{                                                                              \
    return (_enumerated)value;                                                 \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum Enum::_from_integral(Enum::_integral value)        \
{                                                                              \
    return                                                                     \
        better_enums::_or_throw(_from_integral_nothrow(value),                 \
                                "Enum::_from_integral: invalid argument");     \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_optional                                         \
Enum::_from_integral_nothrow(Enum::_integral value)                            \
{                                                                              \
    return                                                                     \
        better_enums::_map_index<Enum>(_ENUM_NS(Enum)::value_array,            \
                                       _from_int_loop(value));                 \
}                                                                              \
                                                                               \
ToStringConstexpr inline const char* Enum::_to_string() const                  \
{                                                                              \
    return                                                                     \
        better_enums::_or_throw(                                               \
            better_enums::_map_index<const char*>(                             \
                _ENUM_NS(Enum)::name_array(),                                  \
                _from_int_loop(CallInitialize(_value))),                       \
            "Enum::to_string: invalid enum value");                            \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum Enum::_from_string(const char *name)               \
{                                                                              \
    return                                                                     \
        better_enums::_or_throw(_from_string_nothrow(name),                    \
                                "Enum::_from_string: invalid argument");       \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_optional                                         \
Enum::_from_string_nothrow(const char *name)                                   \
{                                                                              \
    return                                                                     \
        better_enums::_map_index<Enum>(                                        \
            _ENUM_NS(Enum)::value_array, _from_string_loop(name));             \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum Enum::_from_string_nocase(const char *name)        \
{                                                                              \
    return                                                                     \
        better_enums::_or_throw(_from_string_nocase_nothrow(name),             \
                                "Enum::_from_string_nocase: invalid argument");\
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_optional                                         \
Enum::_from_string_nocase_nothrow(const char *name)                            \
{                                                                              \
    return                                                                     \
        better_enums::_map_index<Enum>(_ENUM_NS(Enum)::value_array,            \
                                       _from_string_nocase_loop(name));        \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline bool Enum::_is_valid(Enum::_integral value)             \
{                                                                              \
    return _from_int_loop(value);                                              \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline bool Enum::_is_valid(const char *name)                  \
{                                                                              \
    return _from_string_loop(name);                                            \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline bool Enum::_is_valid_nocase(const char *name)           \
{                                                                              \
    return _from_string_nocase_loop(name);                                     \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline const char* Enum::_name()                               \
{                                                                              \
    return #Enum;                                                              \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_value_iterable Enum::_values()                   \
{                                                                              \
    return _value_iterable(_ENUM_NS(Enum)::value_array, _size);                \
}                                                                              \
                                                                               \
ToStringConstexpr inline Enum::_name_iterable Enum::_names()                   \
{                                                                              \
    return _name_iterable(_ENUM_NS(Enum)::name_array(), CallInitialize(_size));\
}                                                                              \
                                                                               \
DefineInitialize(Enum)                                                         \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_optional_index                                   \
Enum::_from_int_loop(Enum::_integral value, std::size_t index)                 \
{                                                                              \
    return                                                                     \
        index == _size ? _optional_index() :                                   \
        _ENUM_NS(Enum)::value_array[index]._value == value ?                   \
            _optional_index(index) :                                           \
            _from_int_loop(value, index + 1);                                  \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_optional_index                                   \
Enum::_from_string_loop(const char *name, std::size_t index)                   \
{                                                                              \
    return                                                                     \
        index == _size ? _optional_index() :                                   \
        better_enums::_namesMatch(_ENUM_NS(Enum)::raw_names()[index], name) ?  \
            _optional_index(index) :                                           \
        _from_string_loop(name, index + 1);                                    \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline Enum::_optional_index                                   \
Enum::_from_string_nocase_loop(const char *name, std::size_t index)            \
{                                                                              \
    return                                                                     \
        index == _size ? _optional_index() :                                   \
            better_enums::_namesMatchNocase(                                   \
                _ENUM_NS(Enum)::raw_names()[index], name) ?                    \
                    _optional_index(index) :                                   \
                    _from_string_nocase_loop(name, index + 1);                 \
}                                                                              \
                                                                               \
_ENUM_CONSTEXPR inline bool operator ==(const Enum &a, const Enum &b)          \
    { return a._value == b._value; }                                           \
_ENUM_CONSTEXPR inline bool operator !=(const Enum &a, const Enum &b)          \
    { return a._value != b._value; }                                           \
_ENUM_CONSTEXPR inline bool operator <(const Enum &a, const Enum &b)           \
    { return a._value < b._value; }                                            \
_ENUM_CONSTEXPR inline bool operator <=(const Enum &a, const Enum &b)          \
    { return a._value <= b._value; }                                           \
_ENUM_CONSTEXPR inline bool operator >(const Enum &a, const Enum &b)           \
    { return a._value > b._value; }                                            \
_ENUM_CONSTEXPR inline bool operator >=(const Enum &a, const Enum &b)          \
    { return a._value >= b._value; }



// C++98, C++11
#define _ENUM_CXX98_UNDERLYING_TYPE(Integral)

// C++11
#define _ENUM_CXX11_UNDERLYING_TYPE(Integral)                                  \
    : Integral

// C++98, C++11
#define _ENUM_REGULAR_ENUM_SWITCH_TYPE(Type)                                   \
    _enumerated

// C++11
#define _ENUM_ENUM_CLASS_SWITCH_TYPE(Type)                                     \
    _ENUM_NS(Type)::EnumClassForSwitchStatements

// C++98, C++11
#define _ENUM_REGULAR_ENUM_SWITCH_TYPE_GENERATE(Integral, ...)

// C++11
#define _ENUM_ENUM_CLASS_SWITCH_TYPE_GENERATE(Integral, ...)                   \
    enum class EnumClassForSwitchStatements : Integral { __VA_ARGS__ };

// C++98
#define _ENUM_CXX98_TRIM_STRINGS_ARRAYS(Enum, ...)                             \
    inline const char** raw_names()                                            \
    {                                                                          \
        static const char   *value[] =                                         \
            { _ENUM_ID(_ENUM_STRINGIZE(__VA_ARGS__)) };                        \
        return value;                                                          \
    }                                                                          \
                                                                               \
    inline const char** name_array()                                           \
    {                                                                          \
        static const char   *value[Enum::_size];                               \
        return value;                                                          \
    }                                                                          \
                                                                               \
    inline bool& initialized()                                                 \
    {                                                                          \
        static bool         value = false;                                     \
        return value;                                                          \
    }

// C++11 fast version
#define _ENUM_CXX11_PARTIAL_CONSTEXPR_TRIM_STRINGS_ARRAYS(Enum, ...)           \
    constexpr const char    *the_raw_names[] =                                 \
        { _ENUM_ID(_ENUM_STRINGIZE(__VA_ARGS__)) };                            \
                                                                               \
    constexpr const char * const * raw_names()                                 \
    {                                                                          \
        return the_raw_names;                                                  \
    }                                                                          \
                                                                               \
    inline const char** name_array()                                           \
    {                                                                          \
        static const char   *value[Enum::_size];                               \
        return value;                                                          \
    }                                                                          \
                                                                               \
    inline bool& initialized()                                                 \
    {                                                                          \
        static bool         value = false;                                     \
        return value;                                                          \
    }

// C++11 slow all-constexpr version
#define _ENUM_CXX11_FULL_CONSTEXPR_TRIM_STRINGS_ARRAYS(Enum, ...)              \
    _ENUM_ID(_ENUM_TRIM_STRINGS(__VA_ARGS__))                                  \
                                                                               \
    constexpr const char * const    the_name_array[] =                         \
        { _ENUM_ID(_ENUM_REFER_TO_STRINGS(__VA_ARGS__)) };                     \
                                                                               \
    constexpr const char * const * name_array()                                \
    {                                                                          \
        return the_name_array;                                                 \
    }                                                                          \
                                                                               \
    constexpr const char * const * raw_names()                                 \
    {                                                                          \
        return the_name_array;                                                 \
    }

// C++98, C++11 fast version
#define _ENUM_NO_CONSTEXPR_TO_STRING_KEYWORD

// C++11 slow all-constexpr version
#define _ENUM_CONSTEXPR_TO_STRING_KEYWORD                                      \
    constexpr

// C++98, C++11 fast version
#define _ENUM_DO_DECLARE_INITIALIZE                                            \
    static int initialize();

// C++11 slow all-constexpr version
#define _ENUM_DO_NOT_DECLARE_INITIALIZE

// C++98, C++11 fast version
#define _ENUM_DO_DEFINE_INITIALIZE(Enum)                                       \
    inline int Enum::initialize()                                              \
    {                                                                          \
        if (_ENUM_NS(Enum)::initialized())                                     \
            return 0;                                                          \
                                                                               \
        better_enums::_trim_names(_ENUM_NS(Enum)::raw_names(),                 \
                                  _ENUM_NS(Enum)::name_array(), _size);        \
                                                                               \
        _ENUM_NS(Enum)::initialized() = true;                                  \
                                                                               \
        return 0;                                                              \
    }

// C++11 slow all-constexpr version
#define _ENUM_DO_NOT_DEFINE_INITIALIZE(Enum)

// C++98, C++11 fast version
#define _ENUM_DO_CALL_INITIALIZE(value)                                        \
    better_enums::continue_with(initialize(), value)

// C++11 slow all-constexpr version
#define _ENUM_DO_NOT_CALL_INITIALIZE(value)                                    \
    value



#ifdef BETTER_ENUMS_STRICT_CONVERSION
#   define _ENUM_DEFAULT_SWITCH_TYPE                                           \
        _ENUM_ENUM_CLASS_SWITCH_TYPE
#   define _ENUM_DEFAULT_SWITCH_TYPE_GENERATE                                  \
        _ENUM_ENUM_CLASS_SWITCH_TYPE_GENERATE
#else
#   define _ENUM_DEFAULT_SWITCH_TYPE                                           \
        _ENUM_REGULAR_ENUM_SWITCH_TYPE
#   define _ENUM_DEFAULT_SWITCH_TYPE_GENERATE                                  \
        _ENUM_REGULAR_ENUM_SWITCH_TYPE_GENERATE
#endif



#ifdef _ENUM_HAVE_CONSTEXPR

#ifdef BETTER_ENUMS_CONSTEXPR_TO_STRING
#   define _ENUM_DEFAULT_TRIM_STRINGS_ARRAYS                                   \
        _ENUM_CXX11_FULL_CONSTEXPR_TRIM_STRINGS_ARRAYS
#   define _ENUM_DEFAULT_TO_STRING_KEYWORD                                     \
        _ENUM_CONSTEXPR_TO_STRING_KEYWORD
#   define _ENUM_DEFAULT_DECLARE_INITIALIZE                                    \
        _ENUM_DO_NOT_DECLARE_INITIALIZE
#   define _ENUM_DEFAULT_DEFINE_INITIALIZE                                     \
        _ENUM_DO_NOT_DEFINE_INITIALIZE
#   define _ENUM_DEFAULT_CALL_INITIALIZE                                       \
        _ENUM_DO_NOT_CALL_INITIALIZE
#else
#   define _ENUM_DEFAULT_TRIM_STRINGS_ARRAYS                                   \
        _ENUM_CXX11_PARTIAL_CONSTEXPR_TRIM_STRINGS_ARRAYS
#   define _ENUM_DEFAULT_TO_STRING_KEYWORD                                     \
        _ENUM_NO_CONSTEXPR_TO_STRING_KEYWORD
#   define _ENUM_DEFAULT_DECLARE_INITIALIZE                                    \
        _ENUM_DO_DECLARE_INITIALIZE
#   define _ENUM_DEFAULT_DEFINE_INITIALIZE                                     \
        _ENUM_DO_DEFINE_INITIALIZE
#   define _ENUM_DEFAULT_CALL_INITIALIZE                                       \
        _ENUM_DO_CALL_INITIALIZE
#endif

#define ENUM(Enum, Integral, ...)                                              \
    _ENUM_ID(_ENUM_TYPE(                                                       \
        _ENUM_CXX11_UNDERLYING_TYPE,                                           \
        _ENUM_DEFAULT_SWITCH_TYPE,                                             \
        _ENUM_DEFAULT_SWITCH_TYPE_GENERATE,                                    \
        _ENUM_DEFAULT_TRIM_STRINGS_ARRAYS,                                     \
        _ENUM_DEFAULT_TO_STRING_KEYWORD,                                       \
        _ENUM_DEFAULT_DECLARE_INITIALIZE,                                      \
        _ENUM_DEFAULT_DEFINE_INITIALIZE,                                       \
        _ENUM_DEFAULT_CALL_INITIALIZE,                                         \
        Enum, Integral, __VA_ARGS__))

#define SLOW_ENUM(Enum, Integral, ...)                                         \
    _ENUM_ID(_ENUM_TYPE(                                                       \
        _ENUM_CXX11_UNDERLYING_TYPE,                                           \
        _ENUM_DEFAULT_SWITCH_TYPE,                                             \
        _ENUM_DEFAULT_SWITCH_TYPE_GENERATE,                                    \
        _ENUM_CXX11_FULL_CONSTEXPR_TRIM_STRINGS_ARRAYS,                        \
        _ENUM_CONSTEXPR_TO_STRING_KEYWORD,                                     \
        _ENUM_DO_NOT_DECLARE_INITIALIZE,                                       \
        _ENUM_DO_NOT_DEFINE_INITIALIZE,                                        \
        _ENUM_DO_NOT_CALL_INITIALIZE,                                          \
        Enum, Integral, __VA_ARGS__))

#else

#define ENUM(Enum, Integral, ...)                                              \
    _ENUM_ID(_ENUM_TYPE(                                                       \
        _ENUM_CXX98_UNDERLYING_TYPE,                                           \
        _ENUM_DEFAULT_SWITCH_TYPE,                                             \
        _ENUM_DEFAULT_SWITCH_TYPE_GENERATE,                                    \
        _ENUM_CXX98_TRIM_STRINGS_ARRAYS,                                       \
        _ENUM_NO_CONSTEXPR_TO_STRING_KEYWORD,                                  \
        _ENUM_DO_DECLARE_INITIALIZE,                                           \
        _ENUM_DO_DEFINE_INITIALIZE,                                            \
        _ENUM_DO_CALL_INITIALIZE,                                              \
        Enum, Integral, __VA_ARGS__))

#endif



#endif // #ifndef _BETTER_ENUMS_ENUM_H_
