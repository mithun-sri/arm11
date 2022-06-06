#include <stdio.h>
#include <stdint.h>
#include "instruction.c"

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
#define LAST_BIT_MASK 0x1
#define CPSR_N_OFFSET 31
#define CPSR_Z_OFFSET 30
#define CPSR_C_OFFSET 29
#define CPSR_V_OFFSET 28
#define Z_CLEAR 0xbfffffff
#define C_CLEAR 0xdfffffff
#define V_CLEAR 0xefffffff
#define MOST_SIGNIFICANT 0x80000000

//check update_c functions

void update_n(uint32_t* cpsr, int res) {
  if ((res & MOST_SIGNIFICANT) != 0) {
    *cpsr |= 1 << CPSR_N_OFFSET;
  } else {
    *cpsr &= MOST_SIGNIFICANT;
  }
}

void update_z(uint32_t* cpsr, int res) {
  if (res == 0) {
    *cpsr |= 1 << CPSR_Z_OFFSET;
  } else {
    *cpsr &= Z_CLEAR;
  }
}

void update_c(uint32_t* cpsr, int flag) {
  if (flag == 1) {
    *cpsr |= 1 << CPSR_C_OFFSET;
  } else {
    *cpsr &= C_CLEAR;
  }
}

void update_v(uint32_t* cpsr, int flag) {
  if (flag == 1) {
    *cpsr |= 1 << CPSR_V_OFFSET;
  } else {
    *cpsr &= V_CLEAR;
  }
}

void and(int sBit, uint32_t* cpsr, int rn, int operand2, uint32_t* rd) {
  int res = rn & operand2;
  *rd = res;

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
  }
}

void eor(int sBit, uint32_t* cpsr, int rn, int operand2, uint32_t* rd) {
  int res = rn ^ operand2;
  *rd = res;

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
  }
}

void sub(int sBit, uint32_t* cpsr, int rn, int operand2, uint32_t* rd) {
  int res = rn - operand2;
  int flag = (rn >= operand2);
  *rd = res;

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
    update_c(cpsr, flag);
  }
}

void rsb(int sBit, uint32_t* cpsr, int rn, int operand2, uint32_t* rd) {
  int res = operand2 - rn;
  int flag = (operand2 >= rn);
  *rd = res;

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
    update_c(cpsr, flag);
  }
}

void add(int sBit, uint32_t* cpsr, int rn, int operand2, uint32_t* rd) {
  int res = rn + operand2;
  int flag = (res < rn || res < operand2);
  *rd = res;

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
    update_c(cpsr, flag);
  }
}

void tst(int sBit, uint32_t* cpsr, int rn, int operand2) {
  int res = rn & operand2; 

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
  }
}

void teq(int sBit, uint32_t* cpsr, int rn, int operand2) {
  int res = rn ^ operand2;

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
  }
}

void cmp(int sBit, uint32_t* cpsr, int rn, int operand2) {
  int res = rn - operand2;
  int flag = (rn >= operand2);

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
    update_c(cpsr, flag);
  }
}

void orr(int sBit, uint32_t* cpsr, int rn, int operand2, uint32_t* rd) {
  int res = rn | operand2;
  *rd = res;

  if (sBit) {
    update_n(cpsr, res);
    update_z(cpsr, res);
  }
}

void mov(int sBit, uint32_t* cpsr, int rn, int operand2, uint32_t* rd) {
  *rd = operand2;

  if (sBit) {
    update_n(cpsr, operand2);
    update_z(cpsr, operand2);
  }
}

void manage(uint32_t instruction, struct REGISTERS* r) {
  int bit27 = (instruction & BIT_27_MASK) >> BIT_27_OFFSET;
  int bit26 = (instruction & BIT_26_MASK) >> BIT_26_OFFSET;
  int iBit = (instruction & I_BIT_MASK) >> I_BIT_OFFSET;
  int opcode = (instruction & OPCODE_MASK) >> OPCODE_OFFSET;
  int sBit = (instruction & S_BIT_MASK) >> S_BIT_OFFSET;
  int rnPos = (instruction & RN_MASK) >> RN_OFFSET;
  uint32_t rn = r->general[rnPos];
  int rdPos = (instruction & RD_MASK) >> RD_OFFSET;
  uint32_t *rd = &r->general[rdPos];
  uint16_t operand2 = (instruction & OPERAND_2_MASK);
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
      int lastBit = shift & LAST_BIT_MASK;
      // perform shift
    } else {
      int shiftAmount = shift >> SHIFT_AMOUNT_OFFSET;
      // perform shift
    }
  }

  if (succeeds(instruction, r)) {
    switch (opcode) {
    case 0: and(sBit, cpsr, rn, operand2, rd); break;
    case 1: eor(sBit, cpsr, rn, operand2, rd); break;
    case 2: sub(sBit, cpsr, rn, operand2, rd); break;
    case 3: rsb(sBit, cpsr, rn, operand2, rd); break;
    case 4: add(sBit, cpsr, rn, operand2, rd); break;
    case 8: tst(sBit, cpsr, rn, operand2); break;
    case 9: teq(sBit, cpsr, rn, operand2); break;
    case 10: cmp(sBit, cpsr, rn, operand2); break;
    case 12: orr(sBit, cpsr, rn, operand2, rd); break;
    case 13: mov(sBit, cpsr, rn, operand2, rd); break;
    default: printf("Invalid opcode: Operation not supported\n");
    }
  }
}
