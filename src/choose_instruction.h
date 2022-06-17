#ifndef CHOOSE_INSTRUCTION_H
#define CHOOSE_INSTRUCTION_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "emulate_architecture.h"
#include "emulate_utilities.h"
#include "data_processing.h"
#include "branch.h"
#include "multiply.h"
#include "single_data_transfer.h"
#include "pipeline.h"

struct registers execute_instr(uint32_t instruction, struct registers regs);

void run_emulator(struct registers regs, uint8_t* memory);

void print_register_state(struct registers regs, uint8_t* memory);

#endif
