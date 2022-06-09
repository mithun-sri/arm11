#include <stdio.h>
#include <stdlib.h>

#include "reg.c"
#include "instruction.c"

#define SIGN_EXT_MASK 4227858432     // in binary: 11111100000000000000000000000000

void branch(uint32_t instruction, struct registers regs);
