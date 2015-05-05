#pragma once

#include <cstddef>          // For size_t.
#include <cstring>          // For string and memory routines.
#include <stdexcept>
#include <type_traits>

#include "enum_preprocessor_map.h"



namespace _enum {



#define _ENUM_WEAK      __attribute__((weak))



template <typename EnumType, typename Iterator>
class _Iterable;

template <typename Derived>
class _BaseIterator {
  public:
    Derived& operator ++()
        { ++_index; return static_cast<Derived&>(*this); }
    constexpr bool operator ==(const Derived &other) const
        { return other._index == _index; }
    constexpr bool operator !=(const Derived &other) const
        { return other._index != _index; }

  protected:
    constexpr _BaseIterator(size_t index) : _index(index) { }

    size_t  _index;
};

template <typename EnumType>
class _ValueIterator :
    public _BaseIterator<_ValueIterator<EnumType>> {

    using _Super = _BaseIterator<_ValueIterator<EnumType>>;

  public:
    constexpr typename EnumType::Enumerated operator *() const
        { return EnumType::_value_array[_Super::_index]; }

  private:
    using _Super::_Super;

    friend _Iterable<EnumType, _ValueIterator<EnumType>>;
};

template <typename EnumType>
class _NameIterator :
    public _BaseIterator<_NameIterator<EnumType>> {

    using _Super = _BaseIterator<_NameIterator<EnumType>>;

  public:
    const char* operator *() const
        { return EnumType::_getProcessedName(_Super::_index); }

  private:
    using _Super::_Super;

    friend _Iterable<EnumType, _NameIterator<EnumType>>;
};

template <typename EnumType, typename Iterator>
class _Iterable {
  public:
    using iterator = Iterator;

    constexpr iterator begin() const { return iterator(0); }
    constexpr iterator end() const { return iterator(EnumType::size); }
    constexpr size_t size() const { return EnumType::size; }

  private:
    constexpr _Iterable() { };

    friend EnumType;
};



template <typename UnderlyingType>
class _eat_assign {
  private:
    UnderlyingType  _value;

  public:
    explicit constexpr _eat_assign(UnderlyingType value) : _value(value) { }
    template <typename Any>
    constexpr UnderlyingType operator =(Any dummy) const
        { return _value; }
    constexpr operator UnderlyingType () const { return _value; }
};

#define _ENUM_EAT_ASSIGN_SINGLE(UnderlyingType, expression)                    \
    ((_enum::_eat_assign<UnderlyingType>)UnderlyingType::expression)

#define _ENUM_EAT_ASSIGN(UnderlyingType, ...)                                  \
    _ENUM_PP_MAP(_ENUM_EAT_ASSIGN_SINGLE, UnderlyingType, __VA_ARGS__)



#define _ENUM_STRINGIZE_SINGLE(ignored, expression)     #expression

#define _ENUM_STRINGIZE(...)                                                   \
    _ENUM_PP_MAP(_ENUM_STRINGIZE_SINGLE, ignored, __VA_ARGS__)



#define _ENUM_NAME_ENDERS   "= \t\n"

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



template <typename UnderlyingType>
constexpr UnderlyingType _findMinLoop(const UnderlyingType *values,
                                      size_t valueCount, size_t index,
                                      UnderlyingType best)
{
    return
        index == valueCount ? best :
        values[index] < best ?
            _findMinLoop(values, valueCount, index + 1, values[index]) :
            _findMinLoop(values, valueCount, index + 1, best);
}

template <typename UnderlyingType>
constexpr UnderlyingType _findMin(const UnderlyingType *values,
                                  size_t valueCount)
{
    return _findMinLoop(values, valueCount, 1, values[0]);
}

template <typename UnderlyingType>
constexpr UnderlyingType _findMaxLoop(const UnderlyingType *values,
                                      size_t valueCount, size_t index,
                                      UnderlyingType best)
{
    return
        index == valueCount ? best :
        values[index] > best ?
            _findMaxLoop(values, valueCount, index + 1, values[index]) :
            _findMaxLoop(values, valueCount, index + 1, best);
}

template <typename UnderlyingType>
constexpr UnderlyingType _findMax(const UnderlyingType *values, size_t count)
{
    return _findMaxLoop(values, count, 1, values[0]);
}



static inline const char * const* _processNames(const char * const *rawNames,
                                                size_t count)
{
    // Allocate the replacement names array.
    const char      **processedNames = new const char*[count];
    if (processedNames == nullptr)
        return nullptr;

    // Count the number of bytes needed in the replacement names array (an upper
    // bound).
    size_t          bytesNeeded = 0;
    for (size_t index = 0; index < count; ++index)
        bytesNeeded += std::strlen(rawNames[index]) + 1;

    // Allocate memory for the string data.
    char            *nameStorage = new char[bytesNeeded];
    if (nameStorage == nullptr) {
        delete[] processedNames;
        return nullptr;
    }

    // Trim each name and place the result in storage, then save a pointer to
    // it.
    char            *writePointer = nameStorage;
    for (size_t index = 0; index < count; ++index) {
        const char  *nameEnd =
            std::strpbrk(rawNames[index], _ENUM_NAME_ENDERS);

        size_t      symbolCount =
            nameEnd == nullptr ?
                std::strlen(rawNames[index]) :
                nameEnd - rawNames[index];

        std::strncpy(writePointer, rawNames[index], symbolCount);
        processedNames[index] = writePointer;
        writePointer += symbolCount;

        *writePointer = '\0';
        ++writePointer;
    }

    return processedNames;
}

template <typename EnumType> class _GeneratedArrays;

} // namespace _enum

#define _ENUM_ARRAYS(EnumType, IntegralType, ...)                              \
    enum class EnumType : IntegralType { __VA_ARGS__ };                        \
                                                                               \
    namespace _enum {                                                          \
                                                                               \
    template <>                                                                \
    class _GeneratedArrays<EnumType> {                                         \
      protected:                                                               \
        using Integral = IntegralType;                                         \
        using Enumerated = EnumType;                                           \
                                                                               \
      public:                                                                  \
        constexpr static const char* name = #EnumType;                         \
                                                                               \
      protected:                                                               \
        constexpr static Enumerated        _value_array[] =                    \
            { _ENUM_EAT_ASSIGN(Enumerated, __VA_ARGS__) };                     \
                                                                               \
        constexpr static const char         *_name_array[] =                   \
            { _ENUM_STRINGIZE(__VA_ARGS__) };                                  \
    };                                                                         \
                                                                               \
    }

#define _ENUM_NOT_FOUND     ((size_t)-1)

namespace enum_ {

template <typename EnumType>
class traits : public _enum::_GeneratedArrays<EnumType> {
  protected:
    using _arrays = _enum::_GeneratedArrays<EnumType>;
    using _arrays::_value_array;
    using _arrays::_name_array;

  public:
    using typename _arrays::Enumerated;
    using typename _arrays::Integral;

    constexpr static const size_t       size =
        sizeof(_value_array) / sizeof(Enumerated);
    static_assert(size > 0, "no constants defined in enum type");

    constexpr static const Enumerated   first = _value_array[0];
    constexpr static const Enumerated   last = _value_array[size - 1];
    constexpr static const Enumerated   min =
        _enum::_findMin(_value_array, size);
    constexpr static const Enumerated   max =
        _enum::_findMax(_value_array, size);

    constexpr static const size_t       span =
        (Integral)max - (Integral)min + 1;

    constexpr static Integral to_integral(Enumerated value)
    {
        return (Integral)value;
    }

    constexpr static const Enumerated from_integral(Integral value)
    {
        return _value_array[_from_int_loop(value, true)];
    }

    constexpr static const Enumerated from_integral_unchecked(Integral value)
    {
        return (Enumerated)value;
    }

    static const char* to_string(Enumerated value)
    {
        _processNames();

        for (size_t index = 0; index < size; ++index) {
            if (_value_array[index] == value)
                return _processedNames[index];
        }

        throw std::domain_error("Enum::_to_string: invalid enum value");
    }

    constexpr static const Enumerated from_string(const char *name)
    {
        return _value_array[_from_string_loop(name, true)];
    }

    constexpr static const Enumerated from_string_nocase(const char *name)
    {
        return _value_array[_from_string_nocase_loop(name, true)];
    }

    constexpr static bool is_valid(Integral value)
    {
        return _from_int_loop(value, false) != _ENUM_NOT_FOUND;
    }

    constexpr static bool is_valid(const char *name)
    {
        return _from_string_loop(name, false) != _ENUM_NOT_FOUND;
    }

    constexpr static bool is_valid_nocase(const char *name)
    {
        return _from_string_nocase_loop(name, false) != _ENUM_NOT_FOUND;
    }

  protected:
    static const char * const           *_processedNames;

    static void _processNames()
    {
        if (_processedNames == nullptr)
            _processedNames = _enum::_processNames(_name_array, size);
    }

    static const char* _getProcessedName(size_t index)
    {
        _processNames();
        return _processedNames[index];
    }

    using _ValueIterable =
        _enum::_Iterable<traits, _enum::_ValueIterator<traits>>;
    using _NameIterable =
        _enum::_Iterable<traits, _enum::_NameIterator<traits>>;

    friend _enum::_ValueIterator<traits>;
    friend _enum::_NameIterator<traits>;

  public:
    static const _ValueIterable     values;
    static const _NameIterable      names;

  protected:
    constexpr static size_t _from_int_loop(Integral value,
                                           bool throw_exception,
                                           size_t index = 0)
    {
        return
            index == size ?
                (throw_exception ?
                    throw std::runtime_error(
                        "enum_::traits::from_integral: invalid integer value") :
                    _ENUM_NOT_FOUND) :
            (Integral)_value_array[index] == value ? index :
            _from_int_loop(value, throw_exception, index + 1);
    }

    constexpr static size_t _from_string_loop(const char *name,
                                              bool throw_exception,
                                              size_t index = 0)
    {
        return
            index == size ?
                (throw_exception ?
                    throw std::runtime_error(
                        "enum_::traits::from_string: invalid string argument") :
                    _ENUM_NOT_FOUND) :
            _enum::_namesMatch(_name_array[index], name) ? index :
            _from_string_loop(name, throw_exception, index + 1);
    }

    constexpr static size_t _from_string_nocase_loop(const char *name,
                                                     bool throw_exception,
                                                     size_t index = 0)
    {
        return
            index == size ?
                (throw_exception ?
                    throw std::runtime_error(
                        "enum::traits::_from_string_nocase: "
                        "invalid string argument") :
                    _ENUM_NOT_FOUND) :
                _enum::_namesMatchNocase(_name_array[index], name) ? index :
                _from_string_nocase_loop(name, throw_exception, index + 1);
    }
};

template <typename Enum>
constexpr typename traits<Enum>::Integral to_integral(Enum value)
{
    return traits<Enum>::to_integral(value);
}

template <typename Enum>
constexpr Enum from_integral(typename traits<Enum>::Integral value)
{
    return traits<Enum>::from_integral(value);
}

template <typename Enum>
constexpr Enum from_integral_unchecked(typename traits<Enum>::Integral value)
{
    return traits<Enum>::from_integral_unchecked(value);
}

template <typename Enum>
const char* to_string(Enum value)
{
    return traits<Enum>::to_string(value);
}

template <typename Enum>
constexpr Enum from_string(const char *name)
{
    return traits<Enum>::from_string(name);
}

template <typename Enum>
constexpr Enum from_string_nocase(const char *name)
{
    return traits<Enum>::from_string_nocase(name);
}

} // namespace enum_

#define _ENUM_GLOBALS(EnumType)                                                \
    namespace _enum {                                                          \
                                                                               \
    constexpr _GeneratedArrays<EnumType>::Enumerated _ENUM_WEAK                \
        _GeneratedArrays<EnumType>::_value_array[];                            \
                                                                               \
    constexpr const char * _ENUM_WEAK                                          \
        _GeneratedArrays<EnumType>::_name_array[];                             \
                                                                               \
    }                                                                          \
                                                                               \
    template <>                                                                \
    constexpr enum_::traits<EnumType>::_ValueIterable _ENUM_WEAK               \
        enum_::traits<EnumType>::values{};                                     \
                                                                               \
    template <>                                                                \
    constexpr enum_::traits<EnumType>::_NameIterable _ENUM_WEAK                \
        enum_::traits<EnumType>::names{};                                      \
                                                                               \
    template <>                                                                \
    const char * const * _ENUM_WEAK enum_::traits<EnumType>::_processedNames = \
        nullptr;

#define ENUM(EnumType, Integral, ...)                                          \
    _ENUM_ARRAYS(EnumType, Integral, __VA_ARGS__);                             \
    _ENUM_GLOBALS(EnumType);
