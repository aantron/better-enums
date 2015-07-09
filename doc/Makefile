toexample = ../example/$(notdir $(1:.md=.cc))

SOURCE_MARKDOWN := $(wildcard tutorial/*.md) $(wildcard demo/*.md)
SOURCE_CXX := $(foreach md,$(SOURCE_MARKDOWN),$(call toexample,$(md)))

.PHONY : html
html :
	python docs.py
	@echo "See html/index.html"

.PHONY : publish
publish : prepare
	cp -r html/* ../doc-publish
	cd ../doc-publish && git add . && git commit --amend --reset-author && \
		git push -f

.PHONY : prepare
prepare : examples web

.PHONY : web
web : examples
	python docs.py --web

.PHONY : examples
examples : $(SOURCE_CXX)

define EXAMPLE
$(1) : $(2)
	python transform.py --o-cxx $(1) $(2)
endef

$(foreach md,$(SOURCE_MARKDOWN), \
  		  $(eval $(call EXAMPLE,$(call toexample,$(md)),$(md))))

.PHONY : clean
clean :
	rm -rf html
