#ifndef EMULATE_H
#define EMULATE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BYTES_PER_WORD 4
#define MAX_INSTR_COUNT 16834
#define MEMORY_CAPACITY 65536
#define NUM_REGISTERS 17
#define PC_INDEX 15
#define CPSR_INDEX 16
#define NUM_GEN_PURPOSE_REGISTERS 13

struct registers {
	uint32_t *gen_regs[NUM_GEN_PURPOSE_REGISTERS];
	uint32_t *pc;
	uint32_t cpsr;
};

uint8_t* memory;

#endif
