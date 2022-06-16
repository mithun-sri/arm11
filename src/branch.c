#include "branch.h"

struct registers branch(uint32_t instruction, struct registers regs) {

  if (succeeds(instruction, regs) == 1) {
    uint32_t offset = extract_bits(instruction, 0, 24);
    offset <<= 2;

    if (extract_bits(offset, 24, 25) == 1) {
	    printf("Enters\n");
      offset |= SIGN_EXT_MASK;
    }

    uint32_t branched_instr_addr = *(regs.pc) + offset;
    printf("Offset: %i\n", offset);
    printf("branched pos: %i\n", branched_instr_addr);
    printf("Previous PC: %i\n", *regs.pc);
    *regs.pc = branched_instr_addr;
    printf("New PC: %i\n", *regs.pc);
  }
  return regs;
}
