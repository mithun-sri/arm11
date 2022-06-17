#include "branch.h"

struct registers branch(uint32_t instruction, struct registers regs) {

  if (succeeds(instruction, regs) == 1) {
    uint32_t offset = extract_bits(instruction, 0, 24);
    offset <<= 2;

    if (extract_bits(offset, 25, 26) == 1) {
	    printf("Enters\n");
      int32_t new_offset = offset    // | SIGN_EXT_MASK;
    } else {
      uint32_t new_offset = offset
    }

    uint32_t branched_instr_addr = *(regs.pc) + new_offset;
    printf("Offset: %i\n", new_offset);
    printf("branched pos: %i\n", branched_instr_addr);
    printf("Previous PC: %i\n", *regs.pc);
    *regs.pc = branched_instr_addr;
    printf("New PC: %i\n", *regs.pc);
  }
  return regs;
}
