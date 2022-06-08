#include "emulate_utilities.h"

void manage(uint32_t instruction, struct registers* r) {
    uint8_t bit27 = (instruction >> BIT_27_OFFSET) & LAST_BIT_MASK;
    uint8_t bit26 = (instruction >> BIT_26_OFFSET) & LAST_BIT_MASK;
    uint8_t i_bit = (instruction >> I_BIT_OFFSET) & LAST_BIT_MASK;
    Opcode opcode = (instruction >> OPCODE_OFFSET) & LAST_FOUR_BITS_MASK;
    uint8_t s_bit = (instruction >> S_BIT_OFFSET) & LAST_BIT_MASK;
    uint8_t rn_pos = (instruction >> RN_OFFSET) & LAST_FOUR_BITS_MASK;
    uint32_t rn = r->general[rn_pos];
    uint8_t rd_pos = (instruction >> RD_OFFSET) & LAST_FOUR_BITS_MASK;
    uint8_t *rd = &r->general[rd_pos];
    uint32_t operand2 = (instruction & OPERAND_2_MASK);
    uint32_t *cpsr = &r->cpsr;
  
    if (i_bit) {
        uint8_t rotate = 2 * (operand2 >> ROTATE_OFFSET);
        uint8_t content = operand2 & OPERAND_2_IMMEDIATE_MASK;
        operand2 = rotate_right(rotate, content);
    } else {
        uint8_t* rm_ptr = operand2 & RM_MASK;
        // represents bit no. 4 in shift
        uint8_t optional_bit = (operand2 >> SHIFT_VALUE_OFFSET) & LAST_BIT_MASK;
        Shift shift_type = (operand2 >> SHIFT_TYPE_OFFSET) & LAST_TWO_BITS_MASK;
        uint8_t shift_amount;
        Operand2 new_operand2_with_carry = logical_left_shift(shift_amount, &rm_ptr);

        if (optional_bit) {
            uint8_t *shift_register = operand2 >> RS_OFFSET;
            shift_amount = &shift_register & LAST_BYTE_MASK;
        } else {
            shift_amount = operand2 >> SHIFT_AMOUNT_OFFSET;
        }

        switch(shift_type) {
            case LSL: 
              operand2 = new_operand2_with_carry.value; update_c(cpsr, new_operand2_with_carry.carry); break;
              update_c(cpsr, new_operand2_with_carry.carry);
            case LSR: 
              operand2 = logical_right_shift(shift_amount, &rm_ptr).value; 
              update_c(cpsr, new_operand2_with_carry.carry);
              break;
            case ASR: 
              operand2 = arithmetic_right_shift(shift_amount, &rm_ptr).value; 
              update_c(cpsr, new_operand2_with_carry.carry);
              break;
            case ROR: 
              operand2 = rotate_right(shift_amount, &rm_ptr).value; 
              update_c(cpsr, new_operand2_with_carry.carry);
              break;
            default: printf("shift_type error\n");
        }
    }

    if (succeeds(instruction, r)) {
        switch (opcode) {
        case AND: and(s_bit, cpsr, rn, operand2, rd); break;
        case EOR: eor(s_bit, cpsr, rn, operand2, rd); break;
        case SUB: sub(s_bit, cpsr, rn, operand2, rd); break;
        case RSB: rsb(s_bit, cpsr, rn, operand2, rd); break;
        case ADD: add(s_bit, cpsr, rn, operand2, rd); break;
        case TST: tst(s_bit, cpsr, rn, operand2); break;
        case TEQ: teq(s_bit, cpsr, rn, operand2); break;
        case CMP: cmp(s_bit, cpsr, rn, operand2); break;
        case ORR: orr(s_bit, cpsr, rn, operand2, rd); break;
        case MOV: mov(s_bit, cpsr, rn, operand2, rd); break;
        default: printf("Invalid opcode: Operation not supported\n");
        }
    }
}

int succeeds(uint32_t instruction, struct REGISTERS* r) {
  int cond = instruction >> COND_OFFSET;
  int n = r->cpsr >> CPSR_N_OFFSET;
  int z = (r->cpsr >> CPSR_Z_OFFSET) & LAST_BIT_MASK;
  int c = (r->cpsr >> CPSR_C_OFFSET) & LAST_BIT_MASK;
  int v = (r->cpsr >> CPSR_V_OFFSET) & LAST_BIT_MASK;
  
  int flag;
  
  switch(cond) {
    case EQ: flag = (z == 1); break;
    case NE: flag = (z == 0); break;
    case GE: flag = (n == v); break;
    case LT: flag = (n != v); break;
    case GT: flag = ((z == 0) && (n == v)); break;
    case LE: flag = ((z == 1) || (n != v)); break;
    case AL: flag = 1; break;
    default: printf("Conditional Failure\n");
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
	uint32_t MASK = pow(2, end) - 1;
	return (instr & MASK) >> begin;
}




