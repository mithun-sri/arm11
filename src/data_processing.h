#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

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
	uint32_t val;
} Operand2;

Operand2 logical_left_shift(uint8_t shift_amount, uint32_t content);

Operand2 logical_right_shift(uint8_t shift_amount, uint32_t content);

Operand2 arithmetic_right_shift(uint8_t shift_amount, uint32_t content);

Operand2 rotate_right(uint8_t shift_amount, uint32_t content);

#endif
