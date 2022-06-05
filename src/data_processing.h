#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <stdio.h>
#include <stdint.h>
#include "reg.c"

#define COND_OFFSET 28
#define BIT_27_MASK 0x8000000
#define BIT_27_OFFSET 27
#define BIT_26_MASK 0x4000000
#define BIT_26_OFFSET 26
#define I_BIT_MASK 0x2000000
#define I_BIT_OFFSET 25
#define OPCODE_MASK 0x1e00000
#define OPCODE_OFFSET 21
#define S_BIT_MASK 0x100000
#define S_BIT_OFFSET 20
#define RN_MASK 0xf0000
#define RN_OFFSET 16
#define RD_MASK 0xf000
#define RD_OFFSET 12
#define OPERAND_2_MASK 0xfff
#define OPERAND_2_IMMEDIATE_MASK 0xff
#define ROTATE_OFFSET 8
#define RM_MASK 0xf
#define SHIFT_VALUE_MASK 0xff0
#define SHIFT_OPTIONAL_BIT_MASK 0x10
#define SHIFT_VALUE_OFFSET 4
#define SHIFT_TYPE_MASK 0x6
#define LAST_BIT_OFFSET 1
#define SHIFT_AMOUNT_OFFSET 7
#define SHIFT_LAST_BIT_MASK 0x1

#define NUM_REGISTER_BITS 32
#define MAX_STORE_VALUE (1 << 32 - 1)
#define CARRY 1
#define NO_CARRY 0

typedef enum {
	AND = 0,
	EOR = 1,
	SUB = 2,
	RSB = 3,
	ADD = 4,
	TST = 8,
	TEQ = 9,
	CMP = 10,
	ORR = 12,
	MOV = 13
} Opcode;


typedef enum {
	LSL = 0,
	LSR = 1,
	ASR = 2,
	ROR = 3
} Shift;

typedef struct {
	uint8_t carry;
	uint32_t value;
} Operand2;

int get_carry_bit(uint32_t);

void and(int, int, uint32_t *);

void eor(int, int, uint32_t *);

void sub(int, int, uint32_t *);

void rsb(int, int, uint32_t *);

void add(int, int, uint32_t *);

void tst(int, int);

void teq(int, int);

void cmp(int, int);

void orr(int, int, uint32_t *);

void mov(int, int, uint32_t *);

Operand2 logical_left_shift(uint8_t, uint32_t);

Operand2 logical_right_shift(uint8_t, uint32_t);

Operand2 arithmetic_right_shift(uint8_t, uint32_t);

Operand2 rotate_right(uint8_t, uint32_t);

void manage(uint32_t, struct REGISTERS *);

#endif
