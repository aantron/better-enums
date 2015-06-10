#! /usr/bin/env python

import glob
import os
import os.path
import platform
import re
import shutil
import subprocess
import sys



BASE_DIRECTORY = "platform"
CXXTEST_GENERATED = "cxxtest/tests.cc"

quiet = True
windows = False



def file_title(path):
    return os.path.splitext(os.path.basename(path))[0]



expected_example_outputs = {}

def load_expected_outputs():
    files = glob.glob("expect/*")
    for file in files:
        stream = open(file)
        try:
            content = stream.read()
        finally:
            stream.close()

        expected_example_outputs[file_title(file)] = content



def run(command, catch_warnings = False):
    if not quiet:
        print command

    try:
        output = subprocess.check_output(command.split(),
                                         stderr = subprocess.STDOUT)

        if not catch_warnings:
            return output
        else:
            if re.search("warning", output) != None:
                raise subprocess.CalledProcessError(0, command, output)
            return output

    except subprocess.CalledProcessError as e:
        print e.output
        print command, "failed"
        sys.exit(1)



class Configuration(object):
    def __init__(self, subdirectory, command, skip_examples = []):
        self._subdirectory = subdirectory
        self._command = command
        self._skip_examples = skip_examples

    def elaborate(self, include, output, source):
        command = self._command
        if re.match("clang|[gc]\+\+", command) != None:
            return "%s -I%s -Wall -o %s %s" % (command, include, output, source)
        elif re.match("vc|cl", command) != None:
            return "%s /I%s /Fe%s %s" % (command, include, output, source)
        else:
            raise Exception("unrecognized compiler in '%s'" % command)

    def make_directories(self):
        base = self.directory()
        directories = \
            [base,
             os.path.join(base, "example"),
             os.path.join(base, "cxxtest"),
             os.path.join(base, "link"),
             os.path.join(base, "performance")]

        for directory in directories:
            if not os.path.lexists(directory):
                os.makedirs(directory)

    def make_all(self):
        print self._command

        self.make_directories()

        base = self.directory()

        examples = glob.glob("../example/*.cc")
        example_directory = os.path.join(base, "example")
        for file in examples:
            title = file_title(file)

            if title in self._skip_examples:
                continue

            if title not in expected_example_outputs:
                print "no expected output for example", title
                sys.exit(1)

            binary = os.path.join(example_directory, title) + ".exe"

            command = self.elaborate("..", binary, file)
            run(command, True)

            output = run(binary)
            output = re.sub("\r\n", "\n", output)
            if output != expected_example_outputs[title]:
                print output
                print "output does not match expected output"
                sys.exit(1)

        cxxtest_binary = os.path.join(base, "cxxtest", "tests.exe")
        command = self.elaborate("..", cxxtest_binary, CXXTEST_GENERATED)
        run(command, True)
        run(cxxtest_binary)

        link_sources = glob.glob("link/*.cc")
        link_binary = os.path.join(base, "link", "link.exe")
        command = self.elaborate("..", link_binary, " ".join(link_sources))
        run(command, True)

        performance_sources = glob.glob("performance/*.cc")
        performance_directory = os.path.join(base, "performance")
        for file in performance_sources:
            title = file_title(file)

            binary = os.path.join(performance_directory, title) + ".exe"

            command = "time " + self.elaborate("..", binary, file)
            output = run(command, True)

            output_file = os.path.join(performance_directory, title) + ".times"
            stream = open(output_file, "w")
            try:
                stream.write(output)
            finally:
                stream.close()

    def directory(self):
        return os.path.join(BASE_DIRECTORY, self._subdirectory)



skip_cxx98 = ["101-special-values", "102-bitset", "103-quine", "7-constexpr"]
skip_strict = ["4-switch"]

def modern_gnu(command):
    return [
        Configuration(command + "-c++11", command + " -std=c++11"),
        Configuration(command + "-strict-conversion",
                      command + " -std=c++11 " +
                        "-DBETTER_ENUMS_STRICT_CONVERSION", skip_strict),
        Configuration(command + "-all-constexpr",
                      command + " -std=c++11 " +
                        "-DBETTER_ENUMS_CONSTEXPR_TO_STRING"),
        Configuration(command + "-c++98", command + " -std=c++98", skip_cxx98)
    ]

# g++46 should be one of these, but g++46 c++11 mode currently not supported due
# to the presence of this bug and lack of a workaround in enum.h.
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=54086
def older_gnu(command):
    return [
        Configuration(command + "-c++0x", command + " -std=c++0x"),
        Configuration(command + "-strict-conversion",
                      command + " -std=c++0x " +
                        "-DBETTER_ENUMS_STRICT_CONVERSION", skip_strict),
        Configuration(command + "-all-constexpr",
                      command + " -std=c++0x " +
                        "-DBETTER_ENUMS_CONSTEXPR_TO_STRING"),
        Configuration(command + "-c++98", command + " -std=c++98", skip_cxx98)
    ]

def gnu_pre_constexpr(command):
    return [
        Configuration(command + "-c++0x-noconstexpr-war",
                      command + " -std=c++0x " +
                        "-DBETTER_ENUMS_NO_CONSTEXPR", skip_cxx98),
        Configuration(command + "-strict-conversion",
                      command + " -std=c++0x " +
                        "-DBETTER_ENUMS_NO_CONSTEXPR " +
                        "-DBETTER_ENUMS_STRICT_CONVERSION",
                        skip_cxx98 + skip_strict),
        Configuration(command + "-c++98", command + " -std=c++98", skip_cxx98)
    ]

def gnu_pre_enum_class(command):
    return [
        Configuration(command + "-c++0x-noconstexpr-war",
                      command + " -std=c++0x " +
                        "-DBETTER_ENUMS_NO_CONSTEXPR", skip_cxx98),
        Configuration(command + "-c++98", command + " -std=c++98", skip_cxx98)
    ]

def vc(command):
    return [
        Configuration(command, command + " /EHsc", skip_cxx98),
        Configuration(command + "-strict-conversion",
                      command + " /EHsc /DBETTER_ENUMS_STRICT_CONVERSION",
                      skip_cxx98)
    ]

unix_configurations = \
    modern_gnu("clang++36") + \
    modern_gnu("clang++35") + \
    modern_gnu("clang++34") + \
    modern_gnu("clang++33") + \
    modern_gnu("g++51") + \
    modern_gnu("g++49") + \
    modern_gnu("g++48") + \
    modern_gnu("g++47") + \
    gnu_pre_constexpr("g++46") + \
    gnu_pre_constexpr("g++45") + \
    gnu_pre_constexpr("g++44") + \
    gnu_pre_enum_class("g++43")

windows_configurations = vc("vc2015") + vc("vc2013")

unix_default = Configuration("default", "c++ --std=c++11")

windows_default = Configuration("default", "cl /EHsc")



def main():
    global quiet
    global windows

    load_expected_outputs()

    cxxtest_headers = " ".join(glob.glob(os.path.join("cxxtest", "*.h")))
    run("cxxtestgen --error-printer -o %s %s" %
        (CXXTEST_GENERATED, cxxtest_headers))
    cygwin_fix_command = \
        ("sed 's#\"/home#\"C:/cygwin/home#g' %s > $$$$ ; " + \
        "mv $$$$ %s") % (CXXTEST_GENERATED, CXXTEST_GENERATED)
    os.system(cygwin_fix_command)

    if re.search("Windows|CYGWIN", platform.system()) != None:
        full = windows_configurations
        default = windows_default
        windows = True
    else:
        full = unix_configurations
        default = unix_default

    if len(sys.argv) > 1 and sys.argv[1] == "--all":
        configurations = full
        quiet = True
    else:
        configurations = [default]
        quiet = False

    for configuration in configurations:
        configuration.make_all()

if __name__ == "__main__":
    main()
