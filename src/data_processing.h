#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <stdio.h>
#include <stdint.h>
#include "emulate_architecture.h"
#include "emulate_utilities.h"

#define LAST_FOUR_BITS_MASK 0xf
#define BIT_27_OFFSET 27
#define BIT_26_OFFSET 26
#define I_BIT_OFFSET 25
#define OPCODE_OFFSET 21
#define S_BIT_OFFSET 20
#define RN_OFFSET 16
#define RD_OFFSET 12
#define OPERAND_2_MASK 0xfff
#define OPERAND_2_IMMEDIATE_MASK 0xff
#define ROTATE_OFFSET 8
#define SHIFT_VALUE_OFFSET 4
#define RS_OFFSET 8
#define SHIFT_AMOUNT_OFFSET 7
#define SHIFT_TYPE_OFFSET 5
#define LAST_BIT_MASK 0x1
#define LAST_TWO_BITS_MASK 0x3
#define CPSR_N_OFFSET 31
#define CPSR_Z_OFFSET 30
#define CPSR_C_OFFSET 29
#define CPSR_V_OFFSET 28
#define Z_CLEAR 0xbfffffff
#define C_CLEAR 0xdfffffff
#define V_CLEAR 0xefffffff
#define MOST_SIGNIFICANT 0x80000000
#define MOST_SIGNIFICANT_OFFSET 31
#define REGISTER_BITS 32
#define LAST_BYTE_MASK 0xff
#define RM_MASK 0xf

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

struct registers update_n(struct registers reg, uint32_t res);

struct registers update_z(struct registers reg, uint32_t res);

struct registers update_c(struct registers reg, uint8_t flag);

struct registers update_v(struct registers reg, uint8_t flag);

struct registers and(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd);

struct registers eor(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd);

struct registers sub(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd);

struct registers rsb(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd);

struct registers add(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd);

struct registers tst(struct registers reg, uint8_t sBit, uint8_t rn, uint32_t operand2);

struct registers teq(struct registers reg, uint8_t sBit, uint8_t rn, uint32_t operand2);

struct registers cmp(struct registers reg, uint8_t sBit, uint8_t rn, uint32_t operand2);

struct registers orr(struct registers reg, uint8_t sBit, uint8_t rn, uint32_t operand2, uint8_t rd);

struct registers mov(struct registers reg, uint8_t s_bit, uint32_t operand2, uint8_t rd);

Operand2 logical_left_shift(uint8_t shift_amount, uint32_t content);

Operand2 logical_right_shift(uint8_t shift_amount, uint32_t content);

Operand2 arithmetic_right_shift(uint8_t shift_amount, uint32_t content);

Operand2 rotate_right(uint8_t shift_amount, uint32_t content);

struct registers data_processing(uint32_t instruction, struct registers r);

#endif
