// if the current instruction, currentInstruction is a multiply, then the following code would be run.

#include <stdint.h>

#include "reg.c"
#include "instruction.c"

#define Z_MASK_CPSR 1073741824  // 0100...00 in 32 bit binary
#define N_MASK_CPSR 2147483648  // 1000...00 in 32 bit binary

if (succeeds(instruction, r) == 1) {
  
  uint32_t accumulate = (instruction >> 21) & 1;
  uint32_t set_conditions = (instructions >> 20) & 1;
  
  uint32_t Rn = r.general[(instruction >> 12) & 15];
  uint32_t Rs = r.general[(instruction >> 8) & 15];
  uint32_t Rm = r.general[instruction & 15];

  uint32_t register_to_write_to = (instruction >> 16) & 15;  // need some way of defining registers
  uint32_t result;

  if (accumulate == 1) {
    result = Rm * Rs + Rn;
  
  } else {
    result = Rm * Rs;
  }

  r.general[register_to_write_to] = result;


  if (set_conditions == 1) {
    if (result == 0) {
      r.cpsr |= Z_MASK_CPSR;  
  } else if (result < 0) {
      r.cpsr |= N_MASK_CPSR;
  }
  }

}
  
    
  


