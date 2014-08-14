SHELL:=/bin/bash -e

CC=gcc
OPTS=-Wall -Werror -Wextra -std=c99 -pedantic -g -lm

.PHONY: all clean archive
all: bin/stem

src/%.o: src/%.c
	${CC} ${OPTS} -c $<
	mv $(notdir $*.o) $@

bin/stem: src/stem.c src/dStruct.o
	mkdir -p $(dir $@)
	${CC} $^ -o $@.tmp ${OPTS} -lm
	mv $@.tmp $@

archive: stem.tar.gz

stem.tar.gz: src/stem.c COPYING README.md Makefile
	tar -cvzf stem.tar.gz src/stem.c src/dStruct.c src/dStruct.h COPYING README.md Makefile

clean:
	rm -rf bin/ src/*.o stem.tar.gz
