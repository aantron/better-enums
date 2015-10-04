// This file was generated automatically.

// Bit sets
//
// If you want to use std::bitset or a similar library to have enums be keys
// into a bit set, you need to know the number of bits at compile time. You can
// easily automate this with Better Enums, even when constants are not declared
// in increasing order.

// We simply need to find the maximum value of any given enum type.

#include <bitset>
#include <iostream>
#include <enum.h>

template <typename Enum>
constexpr Enum max_loop(Enum accumulator, size_t index)
{
    return
        index >= Enum::_size() ? accumulator :
        Enum::_values()[index] > accumulator ?
            max_loop<Enum>(Enum::_values()[index], index + 1) :
            max_loop<Enum>(accumulator, index + 1);
}

template <typename Enum>
constexpr Enum max()
{
    return max_loop<Enum>(Enum::_values()[0], 1);
}

// And use that to declare a bit set template:

template <typename Enum>
using EnumSet = std::bitset<max<Enum>()._to_integral() + 1>;

// Now, we can have bit sets that are wide enough to hold whatever range we
// declared. We just declare enums, and the numeric values of their constants
// will be bit indices. The rest is straightforward.

BETTER_ENUM(EFLAGS, int,
            Carry, Parity = 2, Adjust = 4, Zero, Sign, Trap, Interrupt, Direction,
            Overflow, NestedTask = 14, Resume = 16, V8086, AlignmentCheck,
            CPUIDPresent = 21)

int main()
{
    EnumSet<EFLAGS>     eflags = 1 << EFLAGS::Carry | 1 << EFLAGS::Zero;

    if (eflags.test(EFLAGS::Carry))
        eflags.set(EFLAGS::Trap);

    std::cout << eflags << std::endl;

    return 0;
}


// If we want bit sets of fixed known width instead, we can use the code above
// to check that we haven't declared any bit indices out of range:
//
// static_assert(max<EFLAGS>()._to_integral() < 32,
//               "some bit indices are out of range");
