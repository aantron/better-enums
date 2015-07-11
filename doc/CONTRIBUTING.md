# Contributing to Better Enums

All contributions are welcome: feedback, documentation changes, and, of course,
pull requests and patch suggestions. A list of contributors is maintained in the
`CONTRIBUTORS` file. I am grateful to everyone mentioned.

## Some major outstanding issues

- Better Enums currently uses linear scans for lookup, so it could really
  benefit from a lookup data structure that is really fast to generate at
  compile time. All the sorts and other approaches I have tried so far,
  including MPL, Meta, and my own, have been 10-50 times too slow for practical
  use.
- Alternatively, if there is a method to detect whether a given function is
  running at compile or run time, Better Enums could use linear scans during
  compilation, then do a sort at program initialization, and then use fast
  lookups.
- It would be nice if name trimming was always `constexpr`. Right now, this is
  not the default, because it makes compilation of each Better Enum about four
  times slower. Better Enums needs a fast way to take a `const char*`, chop off
  any initializers, and return the new `const char*`.
- I would like to enable more warning flags besides just
  `-Wall -Wextra -pedantic`, but CxxTest triggers the extra warnings.
  `CMakeLists.txt` should probably be modified to add the extra warnings to all
  targets that are not CxxTest tests.

## Testing

I typically write small programs to play around with `enum.h`. The `scratch/`
directory is in `.gitignore` for this purpose. Create `scratch/` and feel free
to do anything you want in it. Once your change is nearly complete, you should
run the automated test suite.

While still actively developing, run `make -C test` to do quick builds. Before
submitting your pull request, run `make -C test default-all`. The first command
tests your code on your system compiler in one configuration, and the second
command tests it in all configurations that your compiler supports.
*Configurations* refers to the optional features of Better Enums, such as
`constexpr` string conversion and using an `enum class` for `switch` statements.

Once your pull request is submitted, the [AppVeyor][appveyor] and
[Travis][travis] web services will automatically test it on many versions of
GCC, Clang, and Visual C++. If you have more than one compiler installed
locally, you can run either the `unix` or `ms` target in `test/Makefile` to test
on a specific compiler. Open the `Makefile` file and find the targets for
instructions.

If your pull request does not include any changes to the code (for example, you
have changed only documentation), add the text `[ci skip]` to the commit message
to prevent AppVeyor and Travis from testing the commit.

The `make` targets mentioned above depend on the following software:

- Make
- CMake
- Python 2
- [CxxTest][cxxtest]

CxxTest's `bin/` directory has to be in `PATH` and the root `cxxtest/` directory
has to be in whatever environment variable your system compiler uses to search
for header files.

On Windows, you also need [Cygwin][cygwin]. The directory containing
`MSBuild.exe` must be in `PATH`.

The programs in `example/` are generated from the Markdown files in
`doc/tutorial/` and `doc/demo/`. If you have edited the Markdown files, you
should run `make -C test examples` to update the example program sources.

If you have created a new example program or compilation performance test, add
it to `test/CMakeLists.txt`. Search for the name of an existing program, such as
`1-hello-world`, and you should see where to add new ones.

[cygwin]:   https://www.cygwin.com
[cxxtest]:  http://cxxtest.com
[appveyor]: https://ci.appveyor.com/project/aantron/better-enums
[travis]:   https://travis-ci.org/aantron/better-enums

## Commits

Please write descriptive commit messages that follow the 50/72 rule. I am likely
to edit commit messages when merging into `master`. I will also squash multiple
commits in most cases. If you prefer I not do either one, let me know, but then
we will have to go back and forth on the exact contents of the pull request.

I am maintaining the `master` branch in such a way that every commit passes its
tests, i.e. `master` is always stable. Every commit going into `master` is first
fully tested in its pull request branch, or in a temporary staging branch, if
necessary.

## Generating the documentation

To generate an offline copy of the documentation, run `make -C doc`. To view it,
open `doc/html/index.html`.
