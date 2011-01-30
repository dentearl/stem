SHELL:=/bin/bash

all: bin/stem

bin/stem: src/stem.c
	mkdir -p bin
	gcc $^ -o $@.tmp -lm
	mv $@.tmp $@

archive: stem.tar.gz

stem.tar.gz: src/stem.c COPYING Makefile
	cd .. && tar -cvzf stem/stem.tar.gz stem/src/stem.c stem/COPYING stem/Makefile

clean:
	rm -rf bin/ 
