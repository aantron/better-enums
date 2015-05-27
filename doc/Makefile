SOURCE_MARKDOWN := $(wildcard tutorial/*) $(wildcard demo/*)
SOURCE_CXX := $(SOURCE_MARKDOWN:.md=.cc)

.PHONY : all
all : html examples

.PHONY : html
html :
	python docs.py

.PHONY : examples
examples : clean-examples $(SOURCE_CXX)

.PHONY : clean-examples
clean-examples :
	make -C ../example clean
	rm -f ../example/*.cc

%.cc : %.md
	python transform.py --o-cxx ../example/$(notdir $@) $<

.PHONY : clean
clean :
	rm -rf html
