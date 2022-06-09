#include "multiply.h"

void multiply(uint32_t instruction, struct registers r) {
  if (succeeds(instruction, r) == 1) {
    uint32_t accumulate = (instruction >> 21) & 1;
    uint32_t set_conditions = (instructions >> 20) & 1;
  
    uint32_t rn = r.general[(instruction >> 12) & 15];
    uint32_t rs = r.general[(instruction >> 8) & 15];
    uint32_t rm = r.general[instruction & 15];

    uint32_t register_to_write_to = (instruction >> 16) & 15;  // need some way of defining registers
    uint32_t result;

    if (accumulate == 1) {
      result = rm * rs + rn;
    } else {
      result = rm * rs;
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
  
    
  



