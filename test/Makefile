# Run "make" for quick builds while developing.
# Run "make default-all" before submitting a pull request.
# Run "make clean" to clean up.
# See doc/CONTRIBUTING.md for full instructions.

CXXTEST_GENERATED := cxxtest/tests.cc

UNIX_MAKE_COMMAND := make
WINDOWS_MAKE_COMMAND := "MSBuild.exe \"Better Enums Testing.sln\""

UNIX_OUTPUT_DIRECTORY := .
WINDOWS_OUTPUT_DIRECTORY := Debug

ifdef COMSPEC
	WIN32 := true
endif
ifdef ComSpec
	WIN32 := true
endif

ifndef WIN32

DEFAULT_MAKE_COMMAND := $(UNIX_MAKE_COMMAND)
DEFAULT_OUTPUT_DIRECTORY := $(UNIX_OUTPUT_DIRECTORY)
define PATH_FIX
@true
endef
SUFFIX :=
CXXTESTGEN := cxxtestgen

else

DEFAULT_MAKE_COMMAND := $(WINDOWS_MAKE_COMMAND)
DEFAULT_OUTPUT_DIRECTORY := $(WINDOWS_OUTPUT_DIRECTORY)
define PATH_FIX
sed 's!include "/!include "C:/cygwin/!g' $1 > $$$$ && mv $$$$ $1
endef
SUFFIX := .exe
CXXTESTGEN := python `which cxxtestgen | sed -E 's!(/cygdrive)?/c/!c:/!'`

endif

DEFAULTS := \
	TITLE=default \
	MAKE_COMMAND=$(DEFAULT_MAKE_COMMAND) \
	OUTPUT_DIRECTORY=$(DEFAULT_OUTPUT_DIRECTORY)

# Builds one configuration with the system compiler. This will be either a
# regular C++11 or C++98 build (no constexpr to_string and no strict
# conversions).
.PHONY : default
default : examples
	make $(DEFAULTS) one-configuration

# Builds all configurations with the system compiler.
.PHONY : default-all
default-all : examples
	make $(DEFAULTS) all-configurations

.PHONY : examples
examples :
	make -C ../doc examples

# Example: make COMPILER=clang++36 unix
.PHONY : unix
unix :
	make TITLE=$(COMPILER) CMAKE_OPTIONS="-DCMAKE_CXX_COMPILER=$(COMPILER)" \
		MAKE_COMMAND=$(UNIX_MAKE_COMMAND) \
		OUTPUT_DIRECTORY=$(UNIX_OUTPUT_DIRECTORY) all-configurations

# Example: make TITLE=vc2013 COMPILER="Visual Studio 12 2013" ms
.PHONY : ms
ms :
	make TITLE=$(TITLE) CMAKE_OPTIONS="-G \\\"$(COMPILER)\\\"" \
		MAKE_COMMAND=$(WINDOWS_MAKE_COMMAND) \
		OUTPUT_DIRECTORY=$(WINDOWS_OUTPUT_DIRECTORY) all-configurations

# Expects three variables to be defined:
# CMAKE_OPTIONS:
#   First, the compiler:
#	- Empty for a "default" build.
# 	- -G "Visual Studio XX YYYY" to select a specific Microsoft compiler.
# 	- -DCMAKE_CXX_COMPILER=AAA to select a specific Unix compiler binary.
#   Configuration selection (e.g. -DCONFIGURATION=CXX98) also go here.
# TITLE:
#	The build title (subdirectory). Some combination of compiler/configuration.
# MAKE_COMMAND:
#	Either make or msbuild "Better Enums Testing.sln"
# OUTPUT_DIRECTORY:
#	Path to generated binaries relative to build directory. Either "." or
#   "Debug".
.PHONY : one-configuration
one-configuration : $(CXXTEST_GENERATED)
	mkdir -p build/$(TITLE)
	cd build/$(TITLE) && cmake $(CMAKE_OPTIONS) ../.. && $(MAKE_COMMAND)
	rm -rf build/$(TITLE)/bin
	[ -f build/$(TITLE)/do-not-test ] || \
		( ln -s $(OUTPUT_DIRECTORY) build/$(TITLE)/bin && \
		make BIN=build/$(TITLE)/bin run-tests )

.PHONY : run-tests
run-tests :
	$(BIN)/cxxtest
	@for FILE in $(BIN)/example-*$(SUFFIX) ; \
	do \
		EXAMPLE=$$(basename $$FILE | sed s/\.exe$$// | sed s/^example-//) ; \
		$$FILE | sed 's/\r$$//' | cmp - expect/$$EXAMPLE ; \
		RESULT=$$? ; \
		if [ $$RESULT -ne 0 ] ; \
		then \
			echo \'$$FILE\' produced bad output ; \
			exit $$RESULT ; \
		fi ; \
	done
	@echo Example program output matches expected output

.PHONY : all-configurations
all-configurations :
	make TITLE=$(TITLE)-c++11 \
		CMAKE_OPTIONS="$(CMAKE_OPTIONS) -DCONFIGURATION=CONSTEXPR" \
		one-configuration
	make TITLE=$(TITLE)-full-constexpr \
		CMAKE_OPTIONS="$(CMAKE_OPTIONS) -DCONFIGURATION=FULL_CONSTEXPR" \
		one-configuration
	make TITLE=$(TITLE)-enum-class \
		CMAKE_OPTIONS="$(CMAKE_OPTIONS) -DCONFIGURATION=STRICT_CONVERSION" \
		one-configuration
	make TITLE=$(TITLE)-c++14 \
		CMAKE_OPTIONS="$(CMAKE_OPTIONS) -DCONFIGURATION=CXX14" \
		one-configuration
	make TITLE=$(TITLE)-c++98 \
		CMAKE_OPTIONS="$(CMAKE_OPTIONS) -DCONFIGURATION=CXX98" \
		one-configuration

.PHONY : all-unix
all-unix : examples
	make COMPILER=clang++39 unix
	make COMPILER=clang++38 unix
	make COMPILER=clang++37 unix
	make COMPILER=g++52 unix
	make COMPILER=g++46 unix
	make COMPILER=g++47 unix
	make COMPILER=g++43 unix
	make COMPILER=g++48 unix
	make COMPILER=g++49 unix
	make COMPILER=g++44 unix
	make COMPILER=g++45 unix
	make COMPILER=clang++33 unix
	make COMPILER=clang++34 unix
	make COMPILER=clang++35 unix
	make COMPILER=clang++36 unix

.PHONY : all-ms
all-ms : examples
	make TITLE=vc2015 COMPILER="Visual Studio 14 2015" ms
	make TITLE=vc2008 COMPILER="Visual Studio 9 2008" ms
	make TITLE=vc2010 COMPILER="Visual Studio 10 2010" ms
	make TITLE=vc2012 COMPILER="Visual Studio 11 2012" ms
	make TITLE=vc2013 COMPILER="Visual Studio 12 2013" ms

$(CXXTEST_GENERATED) : cxxtest/*.h
	$(CXXTESTGEN) --error-printer -o $@ $^
	$(call PATH_FIX,$@)

.PHONY : clean
clean :
	rm -rf build $(CXXTEST_GENERATED)
