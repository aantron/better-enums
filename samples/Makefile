SOURCES := $(wildcard *.cc)
BINARIES := $(SOURCES:.cc=.exe)

CXX := c++
CXXFLAGS := -std=c++11 -Wall -I ..

.PHONY : default
default : run
	@:

.PHONY : all
all : $(BINARIES)

%.exe : %.cc ../*.h Makefile
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY : clean
clean :
	rm -rf *.exe

.PHONY : run
run : all
	@for BINARY in $(BINARIES) ; \
	do \
		echo ./$$BINARY ; \
		./$$BINARY | sed -e "s/^/    /" ; \
	done
