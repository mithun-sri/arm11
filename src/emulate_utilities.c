#include "emulate_utilities.h"

int succeeds(uint32_t instruction, struct registers r) {
  int cond = extract_bits(instruction, 28, 32);
  // printf("COND: %i\n", cond);
  int n = extract_bits(r.cpsr, 31, 32);
  int z = extract_bits(r.cpsr, 30, 31);
/*  int c = (r.cpsr >> CPSR_C_OFFSET) & LAST_BIT_MASK; */
  int v = extract_bits(r.cpsr, 28, 29);
  
  int flag;
  
  switch(cond) {
    case EQ: flag = (z == 1); break;
    case NE: flag = (z == 0); break;
    case GE: flag = (n == v); break;
    case LT: flag = (n != v); break;
    case GT: flag = ((z == 0) && (n == v)); break;
    case LE: flag = ((z == 1) || (n != v)); break;
    case AL: flag = 1; break;
    default: flag = 0;
  }
  return flag;
}

uint8_t get_bit(uint32_t content) {
	return content > 0 ? 1 : 0;
}

uint32_t create_contiguous_mask(uint8_t num_bits) {
	uint32_t mask = 1;
	for (int i=0; i<num_bits-1; i++) {
		mask = mask | mask << 1;
	}
	return mask;
}

int extract_bits(uint32_t instr, uint32_t start, uint32_t end){
	uint32_t carry = 1;
	for (int i = 0; i < end; i++){
		carry *= 2;
	}
	uint32_t MASK = carry - 1;
	return (instr & MASK) >> start;
}
