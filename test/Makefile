.PHONY : default
default :
	python test.py

.PHONY : platform
platform : examples
	python test.py --all

.PHONY : examples
examples :
	make -C ../doc examples

.PHONY : clean
clean :
	rm -rf platform *.obj cxxtest/*.cc cxxtest/*.exe
