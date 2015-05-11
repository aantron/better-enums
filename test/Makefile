ifndef CXX
CXX := c++
endif

ifndef CXXFLAGS
CXXFLAGS := -std=c++11 -Wall -I .. -o
endif

CXXTEST_H := cxxtest/tests.h
CXXTEST_SRC := $(CXXTEST_H:.h=.cc)
CXXTEST_BIN := $(CXXTEST_H:.h=.exe)

LINK_BIN := link/link.exe

PERFORMANCE_SRC := $(wildcard performance/*.cc)
PERFORMANCE_BIN := $(PERFORMANCE_SRC:.cc=.exe)

.PHONY : default
default : run
	@:

$(CXXTEST_SRC) : $(CXXTEST_H) Makefile
	cxxtestgen --error-printer -o $@ $<

$(CXXTEST_BIN) : $(CXXTEST_SRC) ../*.h Makefile
	$(CXX) $(CXXFLAGS) $@ $<
	@echo Passed `grep 'static_assert_1' $(CXXTEST_H) | wc -l` static assertions

$(LINK_BIN) : link/*.h link/*.cc ../*.h Makefile
	$(CXX) $(CXXFLAGS) $@ link/*.cc

$(PERFORMANCE_BIN) : %.exe : %.cc
	@echo $<
	@/usr/bin/time -p $(CXX) $(CXXFLAGS) $@ $<
	@rm $@

.PHONY : run
run : $(CXXTEST_BIN) $(LINK_BIN) $(PERFORMANCE_BIN)
	./$(CXXTEST_BIN)
	./$(LINK_BIN)

.PHONY : clean
clean :
	rm -f $(CXXTEST_SRC)
	find -E . -regex '.*\.exe' | xargs rm -f
