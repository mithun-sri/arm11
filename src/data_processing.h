#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#define NUM_REGISTER_BITS 32
#define MAX_STORE_VALUE (1 << 32 - 1)

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

Operand2 logical_left_shift(uint8_t, uint32_t);

Operand2 logical_right_shift(uint8_t, uint32_t);

Operand2 arithmetic_right_shift(uint8_t, uint32_t);

Operand2 rotate_right(uint8_t, uint32_t);

#endif
