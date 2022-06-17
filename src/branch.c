#include "branch.h"

struct registers branch(uint32_t instruction, struct registers regs) {
	if (succeeds(instruction, regs) == 1) {
		pipe->decoded = 0;
//		pipe->fetched = 0;
		uint32_t offset = extract_bits(instruction, 0, 24);
		offset <<= 2;

		if (extract_bits(offset, 24, 25) == 1){
			offset |= SIGN_EXT_MASK;
		}

		uint32_t branched_instr_addr = *regs.gen_regs[PC_INDEX] + offset;
		*regs.gen_regs[PC_INDEX] = branched_instr_addr;
	}
  return regs;
}
