ifndef CXX
CXX := c++
endif

ifndef CXXFLAGS
CXXFLAGS := -std=c++11 -Wall -I .. -I../extra -o
endif

SOURCES := $(wildcard *.cc)
BINARIES := $(SOURCES:.cc=.exe)

.PHONY : default
default : run
	@:

.PHONY : all
all : $(BINARIES)

%.exe : %.cc ../*.h Makefile
	$(CXX) $(CXXFLAGS) $@ $<

.PHONY : clean
clean :
	rm -rf *.exe *.obj

.PHONY : run
run : all
	@for BINARY in $(BINARIES) ; \
	do \
		echo ./$$BINARY ; \
		./$$BINARY | sed -e "s/^/    /" ; \
	done
