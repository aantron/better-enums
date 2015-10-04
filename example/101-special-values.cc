// This file was generated automatically.

// Special values
//
// Suppose your project has a convention where each enum has special invalid and
// default values - for example, Enum::Invalid is invalid, and the first valid
// constant is default. With Better Enums, you can get the compiler to enforce
// the convention. At the end of this demo, we will have defined functions and
// templates that allow us to write:
//
// Channel     channel = default_;
// Channel     channel = invalid;
//
// void do_something(Channel channel);
//
// do_something(default_);
// do_something(invalid);
//
// The compiler will compute default and invalid values automatically, but the
// programmer will also be able to override the choice. Obviously, the syntax
// above is very legible and maintainable - the intent is clear and your code
// base will respond automatically to changes in enum definitions.
//
// Invalid values
//
// Let's start by defining the invalid values.

#include <iostream>
#include <stdexcept>
#include <enum.h>

// Perhaps the convention is that the invalid value is usually called Invalid,
// but not for all enums. We will encode that using a template function. The
// unspecialized version will encode the default policy:

template <typename Enum>
constexpr Enum invalid_impl() { return Enum::Invalid; }

// A macro allows us to override the invalid value by specializing the template:

#define OVERRIDE_INVALID(Enum, Value)                 \
template<>                                            \
constexpr Enum invalid_impl<Enum>() { return Enum::Value; }

// Now, we can declare enums like these:

BETTER_ENUM(Channel, int, Red, Green, Blue, Invalid)
// Invalid is the invalid value by default

BETTER_ENUM(Compression, int, Undefined, None, Huffman)
OVERRIDE_INVALID(Compression, Undefined)

// and use them:

static_assert(invalid_impl<Channel>() == +Channel::Invalid, "");
static_assert(invalid_impl<Compression>() == +Compression::Undefined, "");

// This even supports enums that don't have an invalid value at all. As long as
// they don't have a constant called Invalid, you will get a compile-time error
// if you try to call invalid_impl<>() on them - as you probably should!
//
// Default values
//
// Perhaps here the convention is the first value that is not invalid is
// default, unless, again, overridden by the programmer. This can be encoded
// using only a slightly more complex template function for the general case:

template <typename Enum>
constexpr Enum default_impl()
{
    return
        Enum::_size() < 2 ?
            throw std::logic_error("enum has no valid constants") :
        Enum::_values()[0] == invalid_impl<Enum>() ?
            Enum::_values()[1] :
            Enum::_values()[0];
}

// The above code gives us the first value if it is not invalid, otherwise the
// second value.
//
// The companion macro for overriding the choice of default value is almost the
// same as it was for invalid. The difference is that we do an extra sanity
// check to make sure the programmer doesn't declare the invalid value to be the
// default. If the sanity check fails, we produce a nice error message. Again,
// we are assuming that this is dictated by policy.

#define OVERRIDE_DEFAULT(Enum, Value)                  \
static_assert(Enum::Value != Enum::Invalid,            \
              #Enum ": default cannot equal invalid"); \
template<>                                             \
constexpr Enum default_impl<Enum>() { return Enum::Value; }

// And, as before, the usage:

static_assert(default_impl<Channel>() == +Channel::Red, "");
static_assert(default_impl<Compression>() == +Compression::None, "");

// And, if you do

BETTER_ENUM(Answer, int, Yes, No, Invalid)
// OVERRIDE_DEFAULT(Answer, Invalid)

// you will get a helpful compile-time error saying Answer: default cannot equal
// invalid.
//
// Making the syntax nicer
//
// At this point, our policy is encoded by the ugly-looking functions
// invalid_impl and default_impl. We want a nicer syntax. The main reason we
// don't just use these functions directly is that the compiler wouldn't infer
// their template arguments from the context. For example, we would have to
// write things like
//
// Channel     channel = invalid_impl<Channel>();
//
// which is unfortunate, because it results in repetition.
//
// In this section, we introduce two global objects called invalid and default_
// that will implicitly convert to any Better Enum type, and provide the invalid
// or default value, respectively, when they do so. They will act as new
// "keywords".

struct invalid_t {
    template <typename To>
    constexpr operator To() const { return invalid_impl<To>(); }
};

struct default_t {
    template <typename To>
    constexpr operator To() const { return default_impl<To>(); }
};

constexpr invalid_t     invalid{};
constexpr default_t     default_{};

// As you can see, both of these provide the families of implicit conversions
// that we need. Now, we can test:

static_assert(+Channel::Invalid == invalid, "");
static_assert(+Compression::Undefined == invalid, "");

static_assert(+Channel::Red == default_, "");
static_assert(+Compression::None == default_, "");

// Finally, we can have nice code such as this:

void dump(Channel channel)
{
    std::cout << channel._to_string() << std::endl;
}

int main()
{
    dump(invalid);

    Channel     channel = default_;
    dump(channel);

    return 0;
}


// There are many possible variations of these policies, but I think most of
// them can be encoded in a reasonable fashion using the tools Better Enums
// provides. Enjoy!
