#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "emulate_architecture.h"

#define COND_OFFSET 28
#define CPSR_N_OFFSET 31
#define CPSR_Z_OFFSET 30
#define CPSR_C_OFFSET 29
#define CPSR_V_OFFSET 28
#define LAST_BIT_MASK 0x1

typedef enum {
	EQ = 0,
	NE = 1,
	GE = 10,
	LT = 11,
    GT = 12,
    LE = 13,
    AL = 14
} CondCode;

uint8_t get_bit(uint32_t content);

uint32_t create_contiguous_mask(uint8_t num_bits);

int succeeds(uint32_t instruction, struct registers);

int extract_bits(uint32_t instr, uint32_t start, uint32_t end);

#endif
