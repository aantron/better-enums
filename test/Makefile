.PHONY : platform
platform :
	make -C ../doc examples
	python test.py

.PHONY : clean
clean :
	rm -rf platform *.obj

.PHONY : default
default : run
	@:
