#include "branch.h"

void branch(uint32_t instruction, struct registers regs) {

  if (succeeds(instruction, regs) == 1) {  // checks if conditions are met for the instruction based                                         on the contents of the register file, r.
    uint32_t mask = ((1 << 24) - 1);
    uint32_t offset = instruction & mask;
    offset <<= 2;

    if (((offset >> 24) & 1) == 1) {
      offset |= SIGN_EXT_MASK;
    }

    uint32_t branched_instr_addr = regs.pc + offset;
    regs.pc = branched_instr_addr;
  }

}


    
