## Extending limits

The `BETTER_ENUM` macro makes heavy use of the preprocessor, and some of the
internal macros have size limits. There are two: on the number of constants you
can declare, and on the maximum length of a constant name under very specific
conditions. If you run into either one, you can extend the limit by following
the instructions on this page.

The second limit, on the maximum length of a constant name, applies only when
you are compiling an enum in
["full" `constexpr`](${prefix}OptInFeatures.html#CompileTimeNameTrimming) mode
*and* the constant has an initializer. Otherwise, your constants can have names
of arbitrary length.

The default limits are 64 constants in an enum and 23 characters for initialized
constants of full-`constexpr` enums. To extend:

  1. Pick your desired limits. I will use 512 constants and 63 characters as an
     example. Add 1 to the number of characters to account for the null
     terminator &mdash; our numbers are now 512 and 64.
  2. Get `make_macros.py` from your copy of the full Better Enums distribution
     or from <a href="https://raw.githubusercontent.com/aantron/better-enums/$ref/script/make_macros.py" download>GitHub</a>.
  3. You will run this script to generate a header file containing some
     replacement macros for `enum.h` to use. Pick a name for this file and a
     location somewhere in your include path. I will assume that this file is
     `common/enum_macros.h` in your project.
  4. Run `python make_macros.py 512 64 > common/enum_macros.h`.
  5. Define `BETTER_ENUMS_MACRO_FILE <common/enum_macros.h>` before including
     `enum.h`. This is typically done by supplying extra flags to the compiler
     on the command line:

     - For g++ and clang++, `-DBETTER_ENUMS_MACRO_FILE='<common/enum_macros.h>'`
     - For VC++, `\DBETTER_ENUMS_MACRO_FILE='<common/enum_macros.h>'`
     - With CMake, you may need something like
       `add_definitions(-DBETTER_ENUMS_MACRO_FILE="$${CMAKE_SOURCE_DIR}/src/enum-macros.h")`

     You can also create a new header file that defines this macro, and then
     includes `enum.h`. Then, include your new file everywhere where you would
     otherwise include `enum.h`:

     ~~~comment
     <em>#pragma once

     #define BETTER_ENUMS_MACRO_FILE <common/enum_macros.h>
     #include <enum.h></em>
     ~~~

  6. Enjoy the looser limits. Just watch out &mdash; increasing the second
     number can really slow down compilation of full-`constexpr` enums.
  7. You don't need `make_macros.py` anymore. It's not part of your build
     process and you can delete it.

---

I am paying attention to feedback, so if more than a few users say that the
default limit of 64 constants is too low, I will increase it to simplify
everyone's command line. The current choice of 64 is basically an arbitrary
guess, loosely informed by the following two facts about macro parameter limits:

- The default limit in Boost.Preprocessor is 64. Though Better Enums does not
  use Boost, I took this number as a guideline.
- The next power of two, 128, is more than [the number Visual C++ supports][vc]
  (127).

[vc]: https://msdn.microsoft.com/en-us/library/ft39hh4x.aspx

%% description =
How to extend limits imposed by internal macros in Better Enums.
