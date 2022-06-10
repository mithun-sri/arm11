CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o

emulate: emulate.o choose_instruction.o data_processing.o branch.o single_data_transfer.o multiply.o emulate_utilities.o -lm
#	cc emulate.o -o emulate

choose_instruction.o: choose_instruction.h choose_instruction.c data_processing.o data_processing.h data_processing.c
#	cc -c choose_instruction.c -o choose_instruction.o

emulate.o: emulate.c emulate_architecture.h
#	cc -c emulate.c -o emulate.o

#emulate.c: emulate_architecture.h
#	echo "idk"

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
rm -f emulate:
