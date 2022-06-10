CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o

emulate: emulate.o
	cc emulate.o -o emulate

emulate.o: emulate.c emulate_architecture.h choose_instruction.c
	cc -c emulate.c -o emulate.o

emulate.c:
	echo "idk"

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
rm -f emulate:
