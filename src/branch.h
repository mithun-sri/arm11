#ifndef BRANCH_H
#define BRANCH_H

#include <stdio.h>
#include <stdlib.h>
#include "emulate_architecture.h"
#include "emulate_utilities.h"

#define SIGN_EXT_MASK 0xFC000000 

struct registers branch(uint32_t instruction, struct registers);

#endif
