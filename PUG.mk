PUG = ./vendor/bin/tale-pug compile
DEP = ./tools/pugdep.pl
pugfiles = $(wildcard view/src/*.pug)
parts 	 = $(wildcard view/src/parts/*.pug)
depfiles = $(patsubst view/src/parts/%.pug, view/dep/%.dep, $(parts) )
phpfiles = $(patsubst view/src/%.pug, view/%.php, $(pugfiles))

all: $(depfiles) $(phpfiles) $(pugfiles) $(parts)

view/dep/%.dep: view/src/parts/%.pug
	touch $@ `cat $@`

view/%.php: view/src/%.pug
		$(PUG) $? $@ --pretty
		$(DEP) $?

