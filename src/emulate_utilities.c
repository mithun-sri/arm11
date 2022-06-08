#include <stdio.h>
#include <stdlib.h>

void manage(uint32_t instruction, struct REGISTERS* r) {
  int bit27 = (instruction & BIT_27_MASK) >> BIT_27_OFFSET;
  int bit26 = (instruction & BIT_26_MASK) >> BIT_26_OFFSET;
  int i_bit = (instruction & I_BIT_MASK) >> I_BIT_OFFSET;
  Opcode opcode = (instruction & OPCODE_MASK) >> OPCODE_OFFSET;
  int s_bit = (instruction & S_BIT_MASK) >> S_BIT_OFFSET;
  int rn_pos = (instruction & RN_MASK) >> RN_OFFSET;
  uint32_t rn = r->general[rn_pos];
  int rd_pos = (instruction & RD_MASK) >> RD_OFFSET;
  uint32_t *rd = &r->general[rd_pos];
  uint16_t operand2 = (instruction & OPERAND_2_MASK);
  uint32_t *cpsr = &r->cpsr;
  
  if (i_bit) {
    int rotate = 2 * (operand2 >> ROTATE_OFFSET);
    int constant = operand2 & OPERAND_2_IMMEDIATE_MASK;
    // operand2 = constant rotated right by rotate value
  } else {
    int rm = operand2 & RM_MASK;
    // represents bit no. 4 in shift
    int optional_bit = (operand2 & SHIFT_OPTIONAL_BIT_MASK) >> SHIFT_VALUE_OFFSET;
    int shift = (operand2 & SHIFT_VALUE_MASK) >> SHIFT_VALUE_OFFSET;
    int shift_type = (shift & SHIFT_TYPE_MASK) >> LAST_BIT_OFFSET;
    
    if (optional_bit) {
      int shift_register = shift >> LAST_BIT_OFFSET;
      int last_bit = shift & LAST_BIT_MASK;
      // perform shift
    } else {
      int shift_amount = shift >> SHIFT_AMOUNT_OFFSET;
      // perform shift
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




