#include "data_processing.h"

uint8_t get_bit(uint32_t content) 
{
	return content > 0 ? 1 : 0;
}

uint32_t create_contiguous_mask(uint8_t num_bits)
{
	uint32_t mask = 1;
	for (int i=0; i<num_bits-1; i++) {
		mask = mask | mask << 1;
	}
	return mask;
}

// add functionality to update CPSR flags
// add functionality to check cond succeeds

void and(int rn, int operand2, uint32_t *rd) {
  int res = rn & operand2;
  *rd = res;
}

void eor(int rn, int operand2, uint32_t *rd) {
  int res = rn ^ operand2;
  *rd = res;
}

void sub(int rn, int operand2, uint32_t *rd) {
  int res = rn - operand2;
  *rd = res;
}

void rsb(int rn, int operand2, uint32_t *rd) {
  int res = operand2 - rn;
  *rd = res;
}

void add(int rn, int operand2, uint32_t *rd) {
  int res = rn + operand2;
  *rd = res;
}

void tst(int rn, int operand2) {
  int res = rn & operand2; 
}

void teq(int rn, int operand2) {
  int res = rn ^ operand2;
}

void cmp(int rn, int operand2) {
  int res = rn - operand2;
}

void orr(int rn, int operand2, uint32_t *rd) {
  int res = rn | operand2;
  *rd = res;
}

void mov(int rn, int operand2, uint32_t *rd) {
  *rd = operand2;
}


Operand2 logical_left_shift(uint8_t shift_amount, uint32_t content) 
{
	Operand2 res;
	res.value = (uint32_t) (content << shift_amount);
	res.carry = get_bit(1 << (NUM_REGISTER_BITS - shift_amount) & content); 

	return res; 
}

Operand2 logical_right_shift(uint8_t shift_amount, uint32_t content)
{
	Operand2 res;
	res.value = (uint32_t) (content >> shift_amount);
	res.carry = get_bit(1 << shift_amount & content); 

	return res; 
}
	
Operand2 arithmetic_right_shift(uint8_t shift_amount, uint32_t content) 
{
	Operand2 res = logical_right_shift(shift_amount, content);
	uint8_t msb = get_bit(MSB_MASK & content);
	for (int i=0; i<shift_amount; i++) {
		res.value = res.value | msb << (MSB_offset - i);	
	}

	return res;
}

Operand2 rotate_right(uint8_t shift_amount, uint32_t content) 
{
	Operand2 res = logical_right_shift(shift_amount, content);
	uint32_t mask = create_contigouous_mask(shift_amount);	
	res.value = res.value & (mask & content) << (MSB_OFFSET - shift_amount); 
	
	return res;
}

void manage(uint32_t instruction, struct REGISTERS* r) {
  int cond = instruction >> COND_OFFSET;
  int bit27 = (instruction & BIT_27_MASK) >> BIT_27_OFFSET;
  int bit26 = (instruction & BIT_26_MASK) >> BIT_26_OFFSET;
  int iBit = (instruction & I_BIT_MASK) >> I_BIT_OFFSET;
  Opcode opcode = (instruction & OPCODE_MASK) >> OPCODE_OFFSET;
  int sBit = (instruction & S_BIT_MASK) >> S_BIT_OFFSET;
  int rnPos = (instruction & RN_MASK) >> RN_OFFSET;
  uint32_t rn = r->general[rnPos];
  int rdPos = (instruction & RD_MASK) >> RD_OFFSET;
  uint32_t *rd = &r->general[rdPos];
  int operand2 = (instruction & OPERAND_2_MASK);
  uint32_t *cpsr = &r->cpsr;
  
  if (iBit) {
    int rotate = 2 * (operand2 >> ROTATE_OFFSET);
    int constant = operand2 & OPERAND_2_IMMEDIATE_MASK;
    // operand2 = constant rotated right by rotate value
  } else {
    int rm = operand2 & RM_MASK;
    // represents bit no. 4 in shift
    int optionalBit = (operand2 & SHIFT_OPTIONAL_BIT_MASK) >> SHIFT_VALUE_OFFSET;
    int shift = (operand2 & SHIFT_VALUE_MASK) >> SHIFT_VALUE_OFFSET;
    int shiftType = (shift & SHIFT_TYPE_MASK) >> LAST_BIT_OFFSET;
    
    if (optionalBit) {
      int shiftRegister = shift >> LAST_BIT_OFFSET;
      int lastBit = shift & SHIFT_LAST_BIT_MASK;
      // perform shift
    } else {
      int shiftAmount = shift >> SHIFT_AMOUNT_OFFSET;
      // perform shift
    }
  }

  switch (opcode) {
    case AND: and(rn, operand2, rd); break;
    case EOR: eor(rn, operand2, rd); break;
    case SUB: sub(rn, operand2, rd); break;
    case RSB: rsb(rn, operand2, rd); break;
    case ADD: add(rn, operand2, rd); break;
    case TST: tst(rn, operand2); break;
    case TEQ: teq(rn, operand2); break;
    case CMP: cmp(rn, operand2); break;
    case ORR: orr(rn, operand2, rd); break;
    case MOV: mov(rn, operand2, rd); break;
    default: printf("Invalid opcode: Operation not supported");
  }
}

