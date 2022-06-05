#include <stdio.h>
#include <stdint.h>
#include "reg.c" // name of file that stores REGISTER struct

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

// add functionality to update CPSR flags
// add functionality to check cond succeeds

void and(int rn, int operand2, uint32_t* rd) {
  int res = rn & operand2;
  *rd = res;
}

void eor(int rn, int operand2, uint32_t* rd) {
  int res = rn ^ operand2;
  *rd = res;
}

void sub(int rn, int operand2, uint32_t* rd) {
  int res = rn - operand2;
  *rd = res;
}

void rsb(int rn, int operand2, uint32_t* rd) {
  int res = operand2 - rn;
  *rd = res;
}

void add(int rn, int operand2, uint32_t* rd) {
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

void orr(int rn, int operand2, uint32_t* rd) {
  int res = rn | operand2;
  *rd = res;
}

void mov(int rn, int operand2, uint32_t* rd) {
  *rd = operand2;
}

void manage(uint32_t instruction, struct REGISTERS* r) {
  int cond = instruction >> COND_OFFSET;
  int bit27 = (instruction & BIT_27_MASK) >> BIT_27_OFFSET;
  int bit26 = (instruction & BIT_26_MASK) >> BIT_26_OFFSET;
  int iBit = (instruction & I_BIT_MASK) >> I_BIT_OFFSET;
  int opcode = (instruction & OPCODE_MASK) >> OPCODE_OFFSET;
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
    case 0: and(rn, operand2, rd); break;
    case 1: eor(rn, operand2, rd); break;
    case 2: sub(rn, operand2, rd); break;
    case 3: rsb(rn, operand2, rd); break;
    case 4: add(rn, operand2, rd); break;
    case 8: tst(rn, operand2); break;
    case 9: teq(rn, operand2); break;
    case 10: cmp(rn, operand2); break;
    case 12: orr(rn, operand2, rd); break;
    case 13: mov(rn, operand2, rd); break;
    default: printf("Invalid opcode: Operation not supported");
  }
}
