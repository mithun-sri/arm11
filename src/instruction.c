#include <stdio.h>
#include "reg.c"

#define COND_OFFSET 28
#define CPSR_N_OFFSET 31
#define CPSR_Z_OFFSET 30
#define CPSR_C_OFFSET 29
#define CPSR_V_OFFSET 28
#define LAST_BIT_MASK 0x1

int succeeds(uint32_t instruction, struct REGISTERS* r) {
  int cond = instruction >> COND_OFFSET;
  int n = r->cpsr >> CPSR_N_OFFSET;
  int z = (r->cpsr >> CPSR_Z_OFFSET) & LAST_BIT_MASK;
  int c = (r->cpsr >> CPSR_C_OFFSET) & LAST_BIT_MASK;
  int v = (r->cpsr >> CPSR_V_OFFSET) & LAST_BIT_MASK;

  int flag;
  
  switch(cond) {
    case 0: flag = (z == 1); break;
    case 1: flag = (z == 0); break;
    case 10: flag = (n == v); break;
    case 11: flag = (n != v); break;
    case 12: flag = ((z == 0) && (n == v)); break;
    case 13: flag = ((z == 1) || (n != v)); break;
    case 14: flag = 1; break;
    default: printf("Conditional Failure\n");
  }

  return flag;
}
