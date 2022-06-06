#include <stdio.h>
#include "reg.c"
#include "instruction.h"

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
