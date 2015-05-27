## Bit sets

If you want to use `std::bitset` or a similar library to use enums as keys into
a bit set, you need to know the number of bits at compile time. You can easily
automate this with Better Enums, even when constants are not declared in
increasing order.

---

We simply need to find the maximum value of any given enum type.

    #include <bitset>
    #include <enum.h>

    template <typename Enum>
    constexpr Enum max_loop(Enum accumulator, size_t index)
    {
        return
            index >= Enum::_size ? accumulator :
            Enum::_values()[index] > accumulator ?
                max_loop<Enum>(Enum::_values()[index], index + 1) :
                max_loop<Enum>(accumulator, index + 1);
    }

    template <typename Enum>
    constexpr Enum max()
    {
        return max_loop<Enum>(Enum::_values()[0], 1);
    }

And use that to declare a bit set template:

    template <typename Enum>
    using EnumSet = std::bitset<max<Enum>()._to_integral() + 1>;

Then rest is straightforward. The only issue is that, in $cxx11, it is necessary
to keep calling `to_integral` on the enums when passing them to `bitset`
functions. You may want to implement a more enum-friendly bit set type, or
overload unary `operator -`.

    ENUM(Channel, int, Red, Green, Blue)
    ENUM(Depth, int, TrueColor = 1, HighColor = 0)

    int main()
    {
        EnumSet<Channel>    channels;
        EnumSet<Depth>      depths;

        return 0;
    }
