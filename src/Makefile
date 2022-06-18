CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -Werror -pedantic
LDLIBS  = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o data_processing_assemble.o multiply_assembler.o special_assemble.o branch_assembler.o assemble_utilities.o

emulate: emulate.o choose_instruction.o emulate_utilities.o data_processing.o single_data_transfer.o multiply.o branch.o

emulate.o: emulate.c
	cc -c emulate.c -o emulate.o

#data_processing.o: data_processing.c emulate_architecture.h emulate_utilities.h
#	cc -c data_processing.c -o data_processing.o

#emulate: emulate.o choose_instruction.o emulate_architecture.h data_processing.o emulate_utilities.o branch.o single_data_transfer.o multiply.o
#	cc  emulate.o choose_instruction.o data_processing.o emulate_utilities.o branch.o single_data_transfer.o multiply.o -o emulate

#choose_instruction.o: choose_instruction.c choose_instruction.h data_processing.h branch.h
#	cc -c choose_instruction.c -o choose_instruction.o

#emulate.o: emulate.c emulate_architecture.h
#	cc -c emulate.c -o emulate.o

#emulate_utilties.o: emulate_utilities.c emulate_architecture.h
#	cc -c emulate_utilities.c -o emulate_utilities.o $(LDLIBS)

#branch.o: branch.c emulate_utilities.h emulate_architecture.h
#	cc -c branch.c -o branch.o

#single_data_transfer.o: single_data_transfer.c emulate_architecture.h emulate_utilities.h data_processing.h
#	cc -c single_data_transfer.c -o single_data_transfer.o $(LDLIBS)

#multiply.o: multiply.c emulate_utilities.h emulate_architecture.h
#	cc -c multiply.c -o multiply.o

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
rm -f emulate:
