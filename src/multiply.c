// if the current instruction, currentInstruction is a multiply, then the following code would be run.

#include "multiply.h"

void multiply(uint32_t instruction, struct registers regs) {

  if (succeeds(instruction, regs) == 1) {
  
    uint32_t accumulate = (instruction >> 21) & 1;
    uint32_t set_conditions = (instructions >> 20) & 1;
  
    uint32_t Rn = regs.general[(instruction >> 12) & 15];
    uint32_t Rs = regs.general[(instruction >> 8) & 15];
    uint32_t Rm = regs.general[instruction & 15];

    uint32_t register_to_write_to = (instruction >> 16) & 15;  // need some way of defining registers
    uint32_t result;

    if (accumulate == 1) {
      result = Rm * Rs + Rn;
  
    } else {
      result = Rm * Rs;
    }

    regs.general_regs[register_to_write_to] = result;


    if (set_conditions == 1) {
      if (result == 0) {
        regs.cpsr |= Z_MASK_CPSR;  
      } else if (result < 0) {
        regs.cpsr |= N_MASK_CPSR;
      }
    }

  }

}



  
    
  



