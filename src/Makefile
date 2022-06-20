CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic
LDLIBS  = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o data_processing_assemble.o multiply_assembler.o special_assemble.o branch_assembler.o assemble_utilities.o single_data_transfer_assemble.o

emulate: emulate.o choose_instruction.o emulate_utilities.o data_processing.o single_data_transfer.o multiply.o branch.o

emulate.o: emulate.c
	cc -c emulate.c -o emulate.o

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
rm -f emulate:
