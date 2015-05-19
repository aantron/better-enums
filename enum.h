// This file is part of Better Enums, released under the BSD 2-clause license.
// See LICENSE for details, or visit http://github.com/aantron/better-enums.

#pragma once

#ifndef _BETTER_ENUMS_ENUM_H_
#define _BETTER_ENUMS_ENUM_H_



#include <cstddef>
#include <stdexcept>

#ifdef BETTER_ENUMS_EXTRA_INCLUDE
#   include BETTER_ENUMS_EXTRA_INCLUDE
#endif



#ifdef BETTER_ENUMS_FORCE_CONSTEXPR
#   define _ENUM_COMPILE_TIME
#else
#   ifdef __GNUC__
#       ifdef __clang__
#           if __has_feature(cxx_constexpr)
#               define _ENUM_COMPILE_TIME
#           endif
#       else
#           if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#               if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#                   define _ENUM_COMPILE_TIME
#               endif
#           endif
#       endif
#   endif
#endif

#ifdef BETTER_ENUMS_FORCE_RUNTIME
#   if defined(_ENUM_COMPILE_TIME)
#       undef _ENUM_COMPILE_TIME
#   endif
#endif

#ifdef _ENUM_COMPILE_TIME
#   define _ENUM_CONSTEXPR      constexpr
#else
#   define _ENUM_CONSTEXPR
#endif

#ifndef __GNUC__
#   define strcasecmp           stricmp
#endif



#ifdef BETTER_ENUMS_MACRO_FILE
#   include BETTER_ENUMS_MACRO_FILE
#else

#define _ENUM_PP_MAP(macro, data, ...) \
    _ENUM_A(_ENUM_PP_MAP_VAR_COUNT, _ENUM_PP_COUNT(__VA_ARGS__)) \
        (macro, data, __VA_ARGS__)

#define _ENUM_PP_MAP_VAR_COUNT(count) _ENUM_M ## count

#define _ENUM_A(macro, ...) macro(__VA_ARGS__)

#define _ENUM_M1(m, d, x) _ENUM_A(m, d, 0, x)
#define _ENUM_M2(m,d,x,...) _ENUM_A(m,d,1,x) _ENUM_M1(m,d,__VA_ARGS__)
#define _ENUM_M3(m,d,x,...) _ENUM_A(m,d,2,x) _ENUM_M2(m,d,__VA_ARGS__)
#define _ENUM_M4(m,d,x,...) _ENUM_A(m,d,3,x) _ENUM_M3(m,d,__VA_ARGS__)
#define _ENUM_M5(m,d,x,...) _ENUM_A(m,d,4,x) _ENUM_M4(m,d,__VA_ARGS__)
#define _ENUM_M6(m,d,x,...) _ENUM_A(m,d,5,x) _ENUM_M5(m,d,__VA_ARGS__)
#define _ENUM_M7(m,d,x,...) _ENUM_A(m,d,6,x) _ENUM_M6(m,d,__VA_ARGS__)
#define _ENUM_M8(m,d,x,...) _ENUM_A(m,d,7,x) _ENUM_M7(m,d,__VA_ARGS__)
#define _ENUM_M9(m,d,x,...) _ENUM_A(m,d,8,x) _ENUM_M8(m,d,__VA_ARGS__)
#define _ENUM_M10(m,d,x,...) _ENUM_A(m,d,9,x) _ENUM_M9(m,d,__VA_ARGS__)
#define _ENUM_M11(m,d,x,...) _ENUM_A(m,d,10,x) _ENUM_M10(m,d,__VA_ARGS__)
#define _ENUM_M12(m,d,x,...) _ENUM_A(m,d,11,x) _ENUM_M11(m,d,__VA_ARGS__)
#define _ENUM_M13(m,d,x,...) _ENUM_A(m,d,12,x) _ENUM_M12(m,d,__VA_ARGS__)
#define _ENUM_M14(m,d,x,...) _ENUM_A(m,d,13,x) _ENUM_M13(m,d,__VA_ARGS__)
#define _ENUM_M15(m,d,x,...) _ENUM_A(m,d,14,x) _ENUM_M14(m,d,__VA_ARGS__)
#define _ENUM_M16(m,d,x,...) _ENUM_A(m,d,15,x) _ENUM_M15(m,d,__VA_ARGS__)
#define _ENUM_M17(m,d,x,...) _ENUM_A(m,d,16,x) _ENUM_M16(m,d,__VA_ARGS__)
#define _ENUM_M18(m,d,x,...) _ENUM_A(m,d,17,x) _ENUM_M17(m,d,__VA_ARGS__)
#define _ENUM_M19(m,d,x,...) _ENUM_A(m,d,18,x) _ENUM_M18(m,d,__VA_ARGS__)
#define _ENUM_M20(m,d,x,...) _ENUM_A(m,d,19,x) _ENUM_M19(m,d,__VA_ARGS__)
#define _ENUM_M21(m,d,x,...) _ENUM_A(m,d,20,x) _ENUM_M20(m,d,__VA_ARGS__)
#define _ENUM_M22(m,d,x,...) _ENUM_A(m,d,21,x) _ENUM_M21(m,d,__VA_ARGS__)
#define _ENUM_M23(m,d,x,...) _ENUM_A(m,d,22,x) _ENUM_M22(m,d,__VA_ARGS__)
#define _ENUM_M24(m,d,x,...) _ENUM_A(m,d,23,x) _ENUM_M23(m,d,__VA_ARGS__)
#define _ENUM_M25(m,d,x,...) _ENUM_A(m,d,24,x) _ENUM_M24(m,d,__VA_ARGS__)
#define _ENUM_M26(m,d,x,...) _ENUM_A(m,d,25,x) _ENUM_M25(m,d,__VA_ARGS__)
#define _ENUM_M27(m,d,x,...) _ENUM_A(m,d,26,x) _ENUM_M26(m,d,__VA_ARGS__)
#define _ENUM_M28(m,d,x,...) _ENUM_A(m,d,27,x) _ENUM_M27(m,d,__VA_ARGS__)
#define _ENUM_M29(m,d,x,...) _ENUM_A(m,d,28,x) _ENUM_M28(m,d,__VA_ARGS__)
#define _ENUM_M30(m,d,x,...) _ENUM_A(m,d,29,x) _ENUM_M29(m,d,__VA_ARGS__)
#define _ENUM_M31(m,d,x,...) _ENUM_A(m,d,30,x) _ENUM_M30(m,d,__VA_ARGS__)
#define _ENUM_M32(m,d,x,...) _ENUM_A(m,d,31,x) _ENUM_M31(m,d,__VA_ARGS__)
#define _ENUM_M33(m,d,x,...) _ENUM_A(m,d,32,x) _ENUM_M32(m,d,__VA_ARGS__)
#define _ENUM_M34(m,d,x,...) _ENUM_A(m,d,33,x) _ENUM_M33(m,d,__VA_ARGS__)
#define _ENUM_M35(m,d,x,...) _ENUM_A(m,d,34,x) _ENUM_M34(m,d,__VA_ARGS__)
#define _ENUM_M36(m,d,x,...) _ENUM_A(m,d,35,x) _ENUM_M35(m,d,__VA_ARGS__)
#define _ENUM_M37(m,d,x,...) _ENUM_A(m,d,36,x) _ENUM_M36(m,d,__VA_ARGS__)
#define _ENUM_M38(m,d,x,...) _ENUM_A(m,d,37,x) _ENUM_M37(m,d,__VA_ARGS__)
#define _ENUM_M39(m,d,x,...) _ENUM_A(m,d,38,x) _ENUM_M38(m,d,__VA_ARGS__)
#define _ENUM_M40(m,d,x,...) _ENUM_A(m,d,39,x) _ENUM_M39(m,d,__VA_ARGS__)
#define _ENUM_M41(m,d,x,...) _ENUM_A(m,d,40,x) _ENUM_M40(m,d,__VA_ARGS__)
#define _ENUM_M42(m,d,x,...) _ENUM_A(m,d,41,x) _ENUM_M41(m,d,__VA_ARGS__)
#define _ENUM_M43(m,d,x,...) _ENUM_A(m,d,42,x) _ENUM_M42(m,d,__VA_ARGS__)
#define _ENUM_M44(m,d,x,...) _ENUM_A(m,d,43,x) _ENUM_M43(m,d,__VA_ARGS__)
#define _ENUM_M45(m,d,x,...) _ENUM_A(m,d,44,x) _ENUM_M44(m,d,__VA_ARGS__)
#define _ENUM_M46(m,d,x,...) _ENUM_A(m,d,45,x) _ENUM_M45(m,d,__VA_ARGS__)
#define _ENUM_M47(m,d,x,...) _ENUM_A(m,d,46,x) _ENUM_M46(m,d,__VA_ARGS__)
#define _ENUM_M48(m,d,x,...) _ENUM_A(m,d,47,x) _ENUM_M47(m,d,__VA_ARGS__)
#define _ENUM_M49(m,d,x,...) _ENUM_A(m,d,48,x) _ENUM_M48(m,d,__VA_ARGS__)
#define _ENUM_M50(m,d,x,...) _ENUM_A(m,d,49,x) _ENUM_M49(m,d,__VA_ARGS__)
#define _ENUM_M51(m,d,x,...) _ENUM_A(m,d,50,x) _ENUM_M50(m,d,__VA_ARGS__)
#define _ENUM_M52(m,d,x,...) _ENUM_A(m,d,51,x) _ENUM_M51(m,d,__VA_ARGS__)
#define _ENUM_M53(m,d,x,...) _ENUM_A(m,d,52,x) _ENUM_M52(m,d,__VA_ARGS__)
#define _ENUM_M54(m,d,x,...) _ENUM_A(m,d,53,x) _ENUM_M53(m,d,__VA_ARGS__)
#define _ENUM_M55(m,d,x,...) _ENUM_A(m,d,54,x) _ENUM_M54(m,d,__VA_ARGS__)
#define _ENUM_M56(m,d,x,...) _ENUM_A(m,d,55,x) _ENUM_M55(m,d,__VA_ARGS__)
#define _ENUM_M57(m,d,x,...) _ENUM_A(m,d,56,x) _ENUM_M56(m,d,__VA_ARGS__)
#define _ENUM_M58(m,d,x,...) _ENUM_A(m,d,57,x) _ENUM_M57(m,d,__VA_ARGS__)
#define _ENUM_M59(m,d,x,...) _ENUM_A(m,d,58,x) _ENUM_M58(m,d,__VA_ARGS__)
#define _ENUM_M60(m,d,x,...) _ENUM_A(m,d,59,x) _ENUM_M59(m,d,__VA_ARGS__)
#define _ENUM_M61(m,d,x,...) _ENUM_A(m,d,60,x) _ENUM_M60(m,d,__VA_ARGS__)
#define _ENUM_M62(m,d,x,...) _ENUM_A(m,d,61,x) _ENUM_M61(m,d,__VA_ARGS__)
#define _ENUM_M63(m,d,x,...) _ENUM_A(m,d,62,x) _ENUM_M62(m,d,__VA_ARGS__)
#define _ENUM_M64(m,d,x,...) _ENUM_A(m,d,63,x) _ENUM_M63(m,d,__VA_ARGS__)

#define _ENUM_PP_COUNT_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, \
    _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
    _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, \
    _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, \
    _58, _59, _60, _61, _62, _63, _64, count, ...) count

#define _ENUM_PP_COUNT(...) _ENUM_PP_COUNT_IMPL(__VA_ARGS__, 64, 63, 62, 61,   \
    60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42,\
    41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23,\
    22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,\
    1)

#define _ENUM_ITERATE(X, f, l) X(f, l, 0) X(f, l, 1) X(f, l, 2) X(f, l, 3)     \
    X(f, l, 4) X(f, l, 5) X(f, l, 6) X(f, l, 7) X(f, l, 8) X(f, l, 9)          \
    X(f, l, 10) X(f, l, 11) X(f, l, 12) X(f, l, 13) X(f, l, 14) X(f, l, 15)    \
    X(f, l, 16) X(f, l, 17) X(f, l, 18) X(f, l, 19) X(f, l, 20) X(f, l, 21)    \
    X(f, l, 22) X(f, l, 23)

#endif // #ifdef BETTER_ENUMS_MACRO_FILE



#define _ENUM_EAT_ASSIGN_SINGLE(EnumType, index, expression)                   \
    ((_enum::_eat_assign<EnumType>)_Base::expression),

#define _ENUM_EAT_ASSIGN(EnumType, ...)                                        \
    _ENUM_PP_MAP(_ENUM_EAT_ASSIGN_SINGLE, EnumType, __VA_ARGS__)



#define _ENUM_NS(EnumType)      _enum::_data_ ## EnumType
#define _ENUM_NAME_ENDERS       "= \t\n"



namespace better_enums {

#ifdef BETTER_ENUMS_USE_OPTIONAL

template <typename T>
using optional = BETTER_ENUMS_USE_OPTIONAL<T>;

#else

template <typename T>
_ENUM_CONSTEXPR T _default()
{
    return (typename T::_Enumerated)0;
}

template <>
_ENUM_CONSTEXPR const char* _default<const char*>()
{
    return nullptr;
}

template <>
_ENUM_CONSTEXPR size_t _default<size_t>()
{
    return 0;
}

template <typename T>
struct optional {
    _ENUM_CONSTEXPR optional() : _valid(false), _value(_default<T>()) { }
    _ENUM_CONSTEXPR optional(T value) : _valid(true), _value(value) { }

    _ENUM_CONSTEXPR const T& operator *() const { return _value; }
    _ENUM_CONSTEXPR const T& operator ->() const { return _value; }

    _ENUM_CONSTEXPR operator bool() const { return _valid; }

    _ENUM_CONSTEXPR const T& value() const { return _value; }

  private:
    bool    _valid;
    T       _value;
};

#endif

}



namespace _enum {

template <typename EnumType>
struct _eat_assign {
    explicit _ENUM_CONSTEXPR _eat_assign(EnumType value) : _value(value) { }
    template <typename Any>
    _ENUM_CONSTEXPR EnumType operator =(Any dummy) const
        { return _value; }
    _ENUM_CONSTEXPR operator EnumType () const { return _value; }

  private:
    EnumType    _value;
};

template <typename Element>
struct _Iterable {
    typedef const Element*  iterator;

    _ENUM_CONSTEXPR iterator begin() const { return iterator(_array); }
    _ENUM_CONSTEXPR iterator end() const { return iterator(_array + _size); }
    _ENUM_CONSTEXPR size_t size() const { return _size; }
    _ENUM_CONSTEXPR const Element& operator [](size_t index) const
        { return _array[index]; }

    _ENUM_CONSTEXPR _Iterable(const Element *array, size_t size) :
        _array(array), _size(size) { };

  private:
    const Element * const   _array;
    const size_t            _size;
};

}



#ifdef _ENUM_COMPILE_TIME



namespace _enum {

template <typename T>
using _optional = better_enums::optional<T>;

template <typename CastTo, typename Element>
constexpr static _optional<CastTo>
_map_index(const Element *array, _optional<size_t> index)
{
    return index ? (CastTo)array[*index] : _optional<CastTo>();
}

template <typename T>
constexpr static T _or_throw(_optional<T> maybe, const char *message)
{
    return maybe ? *maybe : throw std::runtime_error(message);
}

constexpr bool _endsName(char c, size_t index = 0)
{
    return
        // First, test whether c is equal to the current character in
        // _ENUM_NAME_ENDERS. In the case where c is the null terminator, this
        // will cause _endsName to return true when it has exhausted
        // _ENUM_NAME_ENDERS.
        c == _ENUM_NAME_ENDERS[index]    ? true  :
        // If _ENUM_NAME_ENDERS has been exhausted and c never matched, return
        // false.
        _ENUM_NAME_ENDERS[index] == '\0' ? false :
        // Otherwise, go on to the next character in _ENUM_ENDERS.
        _endsName(c, index + 1);
}

constexpr bool _hasExplicitValue(const char *s, size_t index = 0)
{
    return
        s[index] == '\0' ? false :
        s[index] == '=' ? true :
        _hasExplicitValue(s, index + 1);
}

constexpr size_t _constantLength(const char *s, size_t index = 0)
{
    return _endsName(s[index]) ? index : _constantLength(s, index + 1);
}

constexpr char _select(const char *from, size_t from_length, size_t index)
{
    return index >= from_length ? '\0' : from[index];
}

constexpr char _toLowercaseAscii(char c)
{
    return c >= 0x41 && c <= 0x5A ? c + 0x20 : c;
}

constexpr bool _namesMatch(const char *stringizedName,
                           const char *referenceName,
                           size_t index = 0)
{
    return
        // If the current character in the stringized name is a name ender,
        // return true if the reference name ends as well, and false otherwise.
        _endsName(stringizedName[index]) ? referenceName[index] == '\0' :
        // The current character in the stringized name is not a name ender. If
        // the reference name ended, then it is too short, so return false.
        referenceName[index] == '\0'     ? false                        :
        // Neither name has ended. If the two current characters don't match,
        // return false.
        stringizedName[index] !=
            referenceName[index]         ? false                        :
        // Otherwise, if the characters match, continue by comparing the rest of
        // the names.
        _namesMatch(stringizedName, referenceName, index + 1);
}

constexpr bool _namesMatchNocase(const char *stringizedName,
                                 const char *referenceName,
                                 size_t index = 0)
{
    return
        _endsName(stringizedName[index]) ? referenceName[index] == '\0' :
        referenceName[index] == '\0' ? false :
        _toLowercaseAscii(stringizedName[index]) !=
            _toLowercaseAscii(referenceName[index]) ? false :
        _namesMatchNocase(stringizedName, referenceName, index + 1);
}

} // namespace _enum



#define _ENUM_SELECT_SINGLE_CHARACTER(from, from_length, index)                \
    _select(from, from_length, index),

#define _ENUM_SELECT_CHARACTERS(from, from_length)                             \
    _ENUM_ITERATE(_ENUM_SELECT_SINGLE_CHARACTER, from, from_length)



#define _ENUM_TRIM_SINGLE_STRING(ignored, index, expression)                   \
constexpr size_t        _length_ ## index = _constantLength(#expression);      \
constexpr const char    _trimmed_ ## index [] =                                \
    { _ENUM_SELECT_CHARACTERS(#expression, _length_ ## index) };               \
constexpr const char    *_final_ ## index =                                    \
    _hasExplicitValue(#expression) ? _trimmed_ ## index : #expression;

#define _ENUM_TRIM_STRINGS(...)                                                \
    _ENUM_PP_MAP(_ENUM_TRIM_SINGLE_STRING, ignored, __VA_ARGS__)



#define _ENUM_REFER_TO_SINGLE_STRING(ignored, index, expression)               \
    _final_ ## index,

#define _ENUM_REFER_TO_STRINGS(...)                                            \
    _ENUM_PP_MAP(_ENUM_REFER_TO_SINGLE_STRING, ignored, __VA_ARGS__)



#else // #ifdef _ENUM_COMPILE_TIME



#include <cstring>
#include <map>

#define _ENUM_STRINGIZE_SINGLE(ignored, index, expression)      #expression,

#define _ENUM_STRINGIZE(...)                                                   \
    _ENUM_PP_MAP(_ENUM_STRINGIZE_SINGLE, ignored, __VA_ARGS__)

namespace _enum {

void _trim_names(const char * const *raw_names, const char **trimmed_names,
                 size_t count)
{
    for (size_t index = 0; index < count; ++index) {
        size_t      length = std::strcspn(raw_names[index], _ENUM_NAME_ENDERS);
        char        *trimmed = new char[length + 1];

        std::strncpy(trimmed, raw_names[index], length);
        trimmed[length] = '\0';

        trimmed_names[index] = trimmed;
    }
}

}



#endif // #ifdef _ENUM_COMPILE_TIME



#ifdef _ENUM_COMPILE_TIME

#define _ENUM_NOT_DEFAULT_CONSTRUCTIBLE(EnumType)                              \
    EnumType() = delete;

#define _ENUM_SIZED(Integral)           : Integral
#define _ENUM_REPRESENTATION(Integral)  _Enumerated

#else

#define _ENUM_NOT_DEFAULT_CONSTRUCTIBLE(EnumType)                              \
  private:                                                                     \
    EnumType() { }

#define _ENUM_SIZED(Integral)
#define _ENUM_REPRESENTATION(Integral)  Integral

#endif // #ifdef _ENUM_COMPILE_TIME



#define _ENUM_COMMON_DATA(EnumType, Integral, ...)                             \
namespace _enum {                                                              \
namespace _data_ ## EnumType {                                                 \
                                                                               \
struct _Base {                                                                 \
    enum _Enumerated _ENUM_SIZED(Integral) { __VA_ARGS__ };                    \
                                                                               \
    _ENUM_CONSTEXPR _Base(_Enumerated value) : _value(value) { }               \
                                                                               \
    _ENUM_CONSTEXPR bool operator ==(const _Base &other) const                 \
        { return _value == other._value; }                                     \
    _ENUM_CONSTEXPR bool operator ==(_Enumerated value) const                  \
        { return _value == value; }                                            \
    _ENUM_CONSTEXPR bool operator !=(const _Base &other) const                 \
        { return !(*this == other); }                                          \
    _ENUM_CONSTEXPR bool operator !=(_Enumerated value) const                  \
        { return !(*this == value); }                                          \
    _ENUM_CONSTEXPR bool operator <(const _Base &other) const                  \
        { return _value < other._value; }                                      \
    _ENUM_CONSTEXPR bool operator <(_Enumerated value) const                   \
        { return _value < value; }                                             \
    _ENUM_CONSTEXPR bool operator <=(const _Base &other) const                 \
        { return _value <= other._value; }                                     \
    _ENUM_CONSTEXPR bool operator <=(_Enumerated value) const                  \
        { return _value <= value; }                                            \
    _ENUM_CONSTEXPR bool operator >(const _Base &other) const                  \
        { return _value > other._value; }                                      \
    _ENUM_CONSTEXPR bool operator >(_Enumerated value) const                   \
        { return _value > value; }                                             \
    _ENUM_CONSTEXPR bool operator >=(const _Base &other) const                 \
        { return _value >= other._value; }                                     \
    _ENUM_CONSTEXPR bool operator >=(_Enumerated value) const                  \
        { return _value >= value; }                                            \
                                                                               \
    _ENUM_REPRESENTATION(Integral)  _value;                                    \
                                                                               \
    _ENUM_NOT_DEFAULT_CONSTRUCTIBLE(_Base)                                     \
};                                                                             \
                                                                               \
enum _Names { __VA_ARGS__ };                                                   \
                                                                               \
_ENUM_CONSTEXPR const _Base     _value_array[] =                               \
    { _ENUM_EAT_ASSIGN(_Base, __VA_ARGS__) };                                  \
                                                                               \
_ENUM_CONSTEXPR const size_t    _size =                                        \
    sizeof(_value_array) / sizeof(_Base::_Enumerated);                         \
                                                                               \
}                                                                              \
}



#ifdef _ENUM_COMPILE_TIME

#define _ENUM_DATA(EnumType, Integral, ...)                                    \
_ENUM_COMMON_DATA(EnumType, Integral, __VA_ARGS__)                             \
                                                                               \
namespace _enum {                                                              \
namespace _data_ ## EnumType {                                                 \
                                                                               \
enum class _Case : Integral { __VA_ARGS__ };                                   \
                                                                               \
static_assert(_size > 0, "no constants defined in enum type");                 \
                                                                               \
_ENUM_TRIM_STRINGS(__VA_ARGS__);                                               \
                                                                               \
constexpr const char * const    _name_array[] =                                \
    { _ENUM_REFER_TO_STRINGS(__VA_ARGS__) };                                   \
                                                                               \
constexpr const _Iterable<_Base>           _values{_value_array, _size};       \
constexpr const _Iterable<const char*>     _names{_name_array, _size};         \
                                                                               \
}                                                                              \
}

#else

#define _ENUM_DATA(EnumType, Integral, ...)                                    \
_ENUM_COMMON_DATA(EnumType, Integral, __VA_ARGS__)                             \
                                                                               \
namespace _enum {                                                              \
namespace _data_ ## EnumType {                                                 \
                                                                               \
const char                  *_raw_names[] = { _ENUM_STRINGIZE(__VA_ARGS__) };  \
const char                  **_trimmed_names;                                  \
                                                                               \
std::map<Integral, size_t>  _indices_by_value;                                 \
                                                                               \
bool                        _initialized = false;                              \
                                                                               \
}                                                                              \
}

#endif



#ifdef _ENUM_COMPILE_TIME

#define _ENUM_TYPE(EnumType, Integral, ...)                                    \
class EnumType : public _ENUM_NS(EnumType)::_Base {                            \
  protected:                                                                   \
    constexpr static auto   _value_array = _ENUM_NS(EnumType)::_value_array;   \
    constexpr static auto   _name_array  = _ENUM_NS(EnumType)::_name_array;    \
                                                                               \
    template <typename T>                                                      \
    using _optional = better_enums::optional<T>;                               \
                                                                               \
  public:                                                                      \
    using _Integral = Integral;                                                \
                                                                               \
    constexpr static const char     *_name = #EnumType;                        \
    constexpr static const size_t   _size = _ENUM_NS(EnumType)::_size;         \
                                                                               \
    constexpr static const char* _name_()                                      \
    {                                                                          \
        return _name;                                                          \
    }                                                                          \
                                                                               \
    EnumType() = delete;                                                       \
    constexpr EnumType(_Enumerated value) : _Base(value) { }                   \
    constexpr EnumType(_ENUM_NS(EnumType)::_Base value) : _Base(value) { }     \
                                                                               \
    constexpr _Integral to_integral() const                                    \
    {                                                                          \
        return _value;                                                         \
    }                                                                          \
                                                                               \
    constexpr static const _optional<EnumType>                                 \
    _from_integral_nothrow(_Integral value)                                    \
    {                                                                          \
        return                                                                 \
            _enum::_map_index<EnumType>(_value_array, _from_int_loop(value));  \
    }                                                                          \
                                                                               \
    constexpr static const EnumType _from_integral(_Integral value)            \
    {                                                                          \
        return                                                                 \
            _enum::_or_throw(_from_integral_nothrow(value),                    \
                             "Enum::_from_integral: invalid argument");        \
    }                                                                          \
                                                                               \
    constexpr static const EnumType _from_integral_unchecked(_Integral value)  \
    {                                                                          \
        return (_Enumerated)value;                                             \
    }                                                                          \
                                                                               \
    constexpr const char* to_string() const                                    \
    {                                                                          \
        return                                                                 \
            _enum::_or_throw(                                                  \
                _enum::_map_index<const char*>(_name_array,                    \
                                               _from_int_loop(_value)),        \
                "Enum::to_string: invalid enum value");                        \
    }                                                                          \
                                                                               \
    constexpr static const _optional<EnumType>                                 \
    _from_string_nothrow(const char *name)                                     \
    {                                                                          \
        return                                                                 \
            _enum::_map_index<EnumType>(_value_array, _from_string_loop(name));\
    }                                                                          \
                                                                               \
    constexpr static const EnumType _from_string(const char *name)             \
    {                                                                          \
        return                                                                 \
            _enum::_or_throw(_from_string_nothrow(name),                       \
                             "Enum::_from_string: invalid argument");          \
    }                                                                          \
                                                                               \
    constexpr static const _optional<EnumType>                                 \
    _from_string_nocase_nothrow(const char *name)                              \
    {                                                                          \
        return                                                                 \
            _enum::_map_index<EnumType>(_value_array,                          \
                                        _from_string_nocase_loop(name));       \
    }                                                                          \
                                                                               \
    constexpr static const EnumType _from_string_nocase(const char *name)      \
    {                                                                          \
        return                                                                 \
            _enum::_or_throw(_from_string_nocase_nothrow(name),                \
                             "Enum::_from_string_nocase: invalid argument");   \
    }                                                                          \
                                                                               \
    constexpr static bool _is_valid(_Integral value)                           \
    {                                                                          \
        return _from_int_loop(value);                                          \
    }                                                                          \
                                                                               \
    constexpr static bool _is_valid(const char *name)                          \
    {                                                                          \
        return _from_string_loop(name);                                        \
    }                                                                          \
                                                                               \
    constexpr static bool _is_valid_nocase(const char *name)                   \
    {                                                                          \
        return _from_string_nocase_loop(name);                                 \
    }                                                                          \
                                                                               \
    constexpr operator _ENUM_NS(EnumType)::_Case() const                       \
    {                                                                          \
        return (_ENUM_NS(EnumType)::_Case)_value;                              \
    }                                                                          \
                                                                               \
    using _value_iterable = _enum::_Iterable<_ENUM_NS(EnumType)::_Base>;       \
    using _name_iterable  = _enum::_Iterable<const char*>;                     \
                                                                               \
    using _value_iterator = _value_iterable::iterator;                         \
    using _name_iterator  = _name_iterable::iterator;                          \
                                                                               \
    constexpr static const _value_iterable  &_values =                         \
        _ENUM_NS(EnumType)::_values;                                           \
    constexpr static const _name_iterable   &_names =                          \
        _ENUM_NS(EnumType)::_names;                                            \
                                                                               \
    constexpr static const _value_iterable& _values_()                         \
    {                                                                          \
        return _values;                                                        \
    }                                                                          \
                                                                               \
    constexpr static const _name_iterable& _names_()                           \
    {                                                                          \
        return _names;                                                         \
    }                                                                          \
                                                                               \
  protected:                                                                   \
    constexpr static _optional<size_t> _from_int_loop(_Integral value,         \
                                                      size_t index = 0)        \
    {                                                                          \
        return                                                                 \
            index == _size ? _optional<size_t>() :                             \
            _value_array[index]._value == value ? _optional<size_t>(index) :   \
            _from_int_loop(value, index + 1);                                  \
    }                                                                          \
                                                                               \
    constexpr static _optional<size_t> _from_string_loop(const char *name,     \
                                                         size_t index = 0)     \
    {                                                                          \
        return                                                                 \
            index == _size ? _optional<size_t>() :                             \
            _enum::_namesMatch(_name_array[index], name) ?                     \
                _optional<size_t>(index) :                                     \
            _from_string_loop(name, index + 1);                                \
    }                                                                          \
                                                                               \
    constexpr static _optional<size_t>                                         \
        _from_string_nocase_loop(const char *name, size_t index = 0)           \
    {                                                                          \
        return                                                                 \
            index == _size ? _optional<size_t>() :                             \
                _enum::_namesMatchNocase(_name_array[index], name) ?           \
                    _optional<size_t>(index) :                                 \
                _from_string_nocase_loop(name, index + 1);                     \
    }                                                                          \
};

#else // #ifdef _ENUM_COMPILE_TIME

#define _ENUM_TYPE(EnumType, Integral, ...)                                    \
class EnumType : public _ENUM_NS(EnumType)::_Base {                            \
  protected:                                                                   \
    typedef better_enums::optional<EnumType>    _optional;                     \
    typedef better_enums::optional<size_t>      _optional_index;               \
                                                                               \
  public:                                                                      \
    typedef Integral    _Integral;                                             \
                                                                               \
    EnumType(_Enumerated value) : _Base(value) { }                             \
    EnumType(_ENUM_NS(EnumType)::_Base value) : _Base(value) { }               \
                                                                               \
    static const char* _name_()                                                \
    {                                                                          \
        return #EnumType;                                                      \
    }                                                                          \
                                                                               \
    static const size_t     _size = _ENUM_NS(EnumType)::_size;                 \
                                                                               \
    _Integral to_integral() const                                              \
    {                                                                          \
        return _value;                                                         \
    }                                                                          \
                                                                               \
    static _optional _from_integral_nothrow(_Integral value)                   \
    {                                                                          \
        _optional_index     index = _value_to_index(value);                    \
        if (!index)                                                            \
            return _optional();                                                \
                                                                               \
        return EnumType((_Enumerated)value);                                   \
    }                                                                          \
                                                                               \
    static EnumType _from_integral(_Integral value)                            \
    {                                                                          \
        _optional           maybe = _from_integral_nothrow(value);             \
        if (!maybe)                                                            \
            throw std::runtime_error("Enum::_from_integral: invalid argument");\
                                                                               \
        return *maybe;                                                         \
    }                                                                          \
                                                                               \
    static EnumType _from_integral_unchecked(_Integral value)                  \
    {                                                                          \
        return (_Enumerated)value;                                             \
    }                                                                          \
                                                                               \
    const char* to_string() const                                              \
    {                                                                          \
        _optional_index     index = _value_to_index(_value);                   \
        if (!index)                                                            \
            throw std::runtime_error("Enum::to_string: invalid enum value");   \
                                                                               \
        return _ENUM_NS(EnumType)::_trimmed_names[*index];                     \
    }                                                                          \
                                                                               \
    operator _Enumerated() const                                               \
    {                                                                          \
        return (_Enumerated)_value;                                            \
    }                                                                          \
                                                                               \
    static _optional _from_string_nothrow(const char *name)                    \
    {                                                                          \
        _optional_index     index = _string_to_index(name);                    \
        if (!index)                                                            \
            return _optional();                                                \
                                                                               \
        return (EnumType)_ENUM_NS(EnumType)::_value_array[*index];             \
    }                                                                          \
                                                                               \
    static EnumType _from_string(const char *name)                             \
    {                                                                          \
        _optional           maybe = _from_string_nothrow(name);                \
        if (!maybe)                                                            \
            throw std::runtime_error("Enum::_from_string: invalid argument");  \
                                                                               \
        return *maybe;                                                         \
    }                                                                          \
                                                                               \
    static _optional _from_string_nocase_nothrow(const char *name)             \
    {                                                                          \
        _optional_index     index = _string_to_index_nocase(name);             \
        if (!index)                                                            \
            return _optional();                                                \
                                                                               \
        return (EnumType)_ENUM_NS(EnumType)::_value_array[*index];             \
    }                                                                          \
                                                                               \
    static EnumType _from_string_nocase(const char *name)                      \
    {                                                                          \
        _optional           maybe = _from_string_nocase_nothrow(name);         \
        if (!maybe) {                                                          \
            throw std::runtime_error(                                          \
                "Enum::_from_string_nocase: invalid argument");                \
        }                                                                      \
                                                                               \
        return *maybe;                                                         \
    }                                                                          \
                                                                               \
    static bool _is_valid(_Integral value)                                     \
    {                                                                          \
        return _value_to_index(value);                                         \
    }                                                                          \
                                                                               \
    static bool _is_valid(const char *name)                                    \
    {                                                                          \
        return _string_to_index(name);                                         \
    }                                                                          \
                                                                               \
    static bool _is_valid_nocase(const char *name)                             \
    {                                                                          \
        return _string_to_index_nocase(name);                                  \
    }                                                                          \
                                                                               \
    typedef _enum::_Iterable<_ENUM_NS(EnumType)::_Base>     _value_iterable;   \
    typedef _enum::_Iterable<const char*>                   _name_iterable;    \
                                                                               \
    typedef _value_iterable::iterator                       _value_iterator;   \
    typedef _name_iterable::iterator                        _name_iterator;    \
                                                                               \
    static _value_iterable _values_()                                          \
    {                                                                          \
        return _value_iterable(_ENUM_NS(EnumType)::_value_array, _size);       \
    }                                                                          \
                                                                               \
    static _name_iterable _names_()                                            \
    {                                                                          \
        _initialize();                                                         \
        return _name_iterable(_ENUM_NS(EnumType)::_trimmed_names, _size);      \
    }                                                                          \
                                                                               \
  protected:                                                                   \
    static void _initialize()                                                  \
    {                                                                          \
        if (_ENUM_NS(EnumType)::_initialized)                                  \
            return;                                                            \
                                                                               \
        for (size_t index = 0; index < _size; ++index) {                       \
            _ENUM_NS(EnumType)::_indices_by_value[                             \
                _ENUM_NS(EnumType)::_value_array[index]._value] = index;       \
        }                                                                      \
                                                                               \
        _ENUM_NS(EnumType)::_trimmed_names = new const char*[_size];           \
        _enum::_trim_names(_ENUM_NS(EnumType)::_raw_names,                     \
                           _ENUM_NS(EnumType)::_trimmed_names, _size);         \
                                                                               \
        _ENUM_NS(EnumType)::_initialized = true;                               \
    }                                                                          \
                                                                               \
    static _optional_index _value_to_index(_Integral value)                    \
    {                                                                          \
        _initialize();                                                         \
                                                                               \
        std::map<Integral, size_t>::iterator    iterator =                     \
                        _ENUM_NS(EnumType)::_indices_by_value.find(value);     \
                                                                               \
        if (iterator == _ENUM_NS(EnumType)::_indices_by_value.end())           \
            return _optional_index();                                          \
                                                                               \
        return iterator->second;                                               \
    }                                                                          \
                                                                               \
    static _optional_index _string_to_index(const char *s)                     \
    {                                                                          \
        _initialize();                                                         \
                                                                               \
        for (size_t index = 0; index < _size; ++index) {                       \
            if (std::strcmp(s, _ENUM_NS(EnumType)::_trimmed_names[index]) == 0)\
                return index;                                                  \
        }                                                                      \
                                                                               \
        return _optional_index();                                              \
    }                                                                          \
                                                                               \
    static _optional_index _string_to_index_nocase(const char *s)              \
    {                                                                          \
        _initialize();                                                         \
                                                                               \
        for (size_t index = 0; index < _size; ++index) {                       \
            if (strcasecmp(s, _ENUM_NS(EnumType)::_trimmed_names[index]) == 0) \
                return index;                                                  \
        }                                                                      \
                                                                               \
        return _optional_index();                                              \
    }                                                                          \
                                                                               \
  private:                                                                     \
    EnumType() : _Base((_Enumerated)0) { }                                     \
};

#endif // #ifdef _ENUM_COMPILE_TIME



#define _ENUM_OPERATORS(EnumType)                                              \
_ENUM_CONSTEXPR const EnumType operator +(EnumType::_Enumerated enumerated)    \
    { return (EnumType)enumerated; }                                           \
                                                                               \
namespace _enum {                                                              \
namespace _data_ ## EnumType {                                                 \
                                                                               \
_ENUM_CONSTEXPR const EnumType operator +(_ENUM_NS(EnumType)::_Base base)      \
    { return (EnumType)base; }                                                 \
                                                                               \
}                                                                              \
}



#define ENUM(EnumType, Integral, ...)                                          \
    _ENUM_DATA(EnumType, Integral, __VA_ARGS__);                               \
    _ENUM_TYPE(EnumType, Integral, __VA_ARGS__);                               \
    _ENUM_OPERATORS(EnumType);



#endif // #ifndef _BETTER_ENUMS_ENUM_H_
