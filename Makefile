SHELL:=/bin/bash

all: bin/stem

bin/stem: src/stem.c
	mkdir -p bin
	gcc $^ -o $@.tmp
	mv $@.tmp $@

archive: stem.tar.gz

stem.tar.gz:
	cd .. && tar -cvzf stem/stem.tar.gz stem/src/stem.c stem/COPYING stem/Makefile

clean:
	rm -rf bin/ 