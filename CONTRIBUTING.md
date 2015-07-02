# Contributing to Better Enums

All contributions are welcome: feedback, documentation changes, and, of course,
pull requests and patch suggestions. A list of contributors is maintained in the
`CONTRIBUTORS` file. I am grateful to everyone mentioned.

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

## Generating the documentation

To generate an offline copy of the documentation, run `make -C doc`. To view it,
open `doc/html/index.html`.
