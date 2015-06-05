.PHONY : default
default :
	make -C ../doc examples
	python test.py

.PHONY : platform
platform :
	make -C ../doc examples
	python test.py --all

.PHONY : clean
clean :
	rm -rf platform *.obj
