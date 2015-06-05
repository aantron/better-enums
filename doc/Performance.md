## Performance

A basic performance test is run on
[every compiler tested](${prefix}CompilerSupport.html#TestedConfigurations). It
doesn't try to be very accurate &mdash; it just stress-tests the compiler once
to get a rough idea of how long it takes to compile Better Enums.

The files compared in the test are as follows:

  - [One file]($repo/blob/$version/test/performance/4-declare_enums.cc) includes
    `enum.h` and declares 647 constants across 36 Better Enums.
  - The [other file]($repo/blob/$version/test/performance/5-iostream.cc) *only*
    includes `iostream` and does nothing with it.

The argument is that if compiling a bunch of Better Enums is faster, or about as
fast as, including a single standard header such as `iostream`, then Better
Enums is fast enough for general use.

Results are given for select compilers and
[configurations](${prefix}CompilerSupport.html#CompileTimeReflectionConfigurations)
as ratios of how long it took to compile the Better Enums file to how long it
took to compile the `iostream` file. The less the ratio, the better. Ratios less
than 1 mean the enums compiled faster, and ratios greater than 1 mean `iostream`
compiled faster.

  - clang 3.6, fast `constexpr`: 0.66
  - clang 3.6, full `constexpr`: 2.25
  - gcc 5.1, fast `constexpr`: 1.58
  - gcc 5.1, full `constexpr`: 4.23
  - VC2015RC, $cxx98: 1.18

%% description = Compilation performance testing results.
