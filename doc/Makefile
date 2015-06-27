SOURCE_MARKDOWN := $(wildcard tutorial/*) $(wildcard demo/*)
SOURCE_CXX := $(SOURCE_MARKDOWN:.md=.cc)

.PHONY : html
html :
	python docs.py
	@echo "See html/index.html"

.PHONY : publish
publish : prepare
	cp -r html ../doc-publish
	git commit --amend
	git push -f

.PHONY : prepare
prepare : examples web

.PHONY : web
web : examples
	python docs.py --web

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
