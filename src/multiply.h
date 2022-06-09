#ifndef MULTIPLY_H
#define MULTIPLY_H
#include <stdint.h>
#include "emulate_utilities.h"
#include "emulate_architecture.h"

#define Z_MASK_CPSR 1073741824  // 0100...00 in 32 bit binary
#define N_MASK_CPSR 2147483648  // 1000...00 in 32 bit binary

void multiply(uint32_t instruction, struct registers r);

#endif
