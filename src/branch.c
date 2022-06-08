#include <stdio.h>
#include <stdlib.h>
#include "emulate_utilities.h"

#define SIGN_EXT_MASK 4227858432     // in binary: 11111100000000000000000000000000


if (succeeds(instruction, r) == 1) {  // checks if conditions are met for the instruction based                                         on the contents of the register file, r.
  uint32_t mask = ((1 << 24) - 1);
  uint32_t offset = instruction & mask;
  offset <<= 2;

  if (((offset >> 24) & 1) == 1) {
    offset |= SIGN_EXT_MASK;
  }

  uint32_t branched_instr_addr = r.pc + offset;
  registers.pc = branched_instr_addr;
}
    
