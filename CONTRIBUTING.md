# Working on Better Enums

All contributions are welcome &mdash; feedback, documentation review, and, of
course, pull requests, or patch suggestions. A list of contributors is
maintained in the CONTRIBUTORS file. I am grateful to everyone mentioned.

## Working on code

The development environment is in a fairly embryonic state. For example, the
automatic test suite isn't that easy to set up to work with VC++. If you want to
develop with VC++, *please* send me an email at
[antonbachin@yahoo.com](mailto:antonbachin@yahoo.com) and I will get on
improving it speedily. For now, the easiest way to develop on Windows is to
install GCC or clang from [Cygwin][cygwin].

If your change includes code, you will want to test it. Here is how to do this.
Basic testing is currently only supported in a reasonable automated fashion on
GCC-like C++11 compilers, i.e. GCC and clang. First, you will need:

  - A C++ compiler,
  - Python 2.7,
  - Make, and
  - [CxxTest][cxxtest].

If you also want to edit the documentation and re-generate the examples from the
tutorial Markdown, you will need the [mistune][mistune] library for Python.

Clone the repository and make your changes against `master`. To test, go to the
`test/` directory and run `./test.py`. This script assumes that your GCC-like
system compiler is symlinked as `c++` (generally true) and accepts `-std=c++11`.
The script will build and run the unit test, compare the example programs'
output against expected output, and do a test that links two translation units
that declare the same enum. If the exit status is zero, your change probably
didn't break anything.

The reason I say *probably* is because the change actually needs to be tested on
a large number of compilers and in various configurations, but I can't expect
you to do that. Go ahead and submit your GitHub pull request, and I will do the
testing myself and let you know if there are any problems, and probably how to
fix them. If you don't want to go through the tedium of fixing them without
being able to test yourself, then I hope you will allow me to take your patch,
apply whatever changes are needed to get it to pass on all compilers, and then
apply it to `master` and give you credit with `git commit --author`. I will let
you know exactly what I'm doing to your code before I apply it, and you can, of
course, request further changes or refuse.

---

If you want to run only the samples, go to `example/` and run `make`. This makes
the same assumptions by default: your system compiler is `c++` and it accepts
`-std=c++11`.

---

The rest of this file describes the testing process I will do, in case you want
to try it yourself.

If you run `./test.py --all` on a Unix-like system, the script will assume that
you have symlinks `clang33` to `clang36` and `gcc43` to `gcc51`. It will run the
same tests as mentioned above, but on every one of those compilers.

Similarly, if you run `./test.py --all` on a Windows system, it will assume that
you have binaries `vc2013` and `vc2015`. These are actually scripts on my
development machine that pass the right options to the different verisons of
`cl.exe`. It's pretty crufty at this point.

---

The reason I am not working on improving this immediately is because I am
looking into using some kind of third-party service. I really don't expect
anyone to install multiple GCC-like and Microsoft compilers to work on the code.
It would be nice if code changes could be submitted over the network by some
script and tested on a remote machine, or machines, that have all of this
installed and configured.

[cygwin]:  https://www.cygwin.com
[cxxtest]: http://cxxtest.com
[mistune]: https://github.com/lepture/mistune
