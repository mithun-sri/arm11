#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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

#endif
