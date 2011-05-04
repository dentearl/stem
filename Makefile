SHELL:=/bin/bash

all: bin/stem

src/%.o: src/%.c
	gcc -g -Wall -c $<
	mv $(notdir $*.o) $@

bin/stem: src/stem.c src/dStruct.o
	mkdir -p $(dir $@)
	gcc $^ -o $@.tmp -lm
	mv $@.tmp $@

archive: stem.tar.gz

stem.tar.gz: src/stem.c COPYING Makefile
	cd .. && tar -cvzf stem/stem.tar.gz stem/src/stem.c stem/COPYING stem/Makefile

clean:
	rm -rf bin/ 
