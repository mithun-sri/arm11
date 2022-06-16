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

struct data_pipeline {
  uint32_t fetched;
  uint32_t decoded;
  uint8_t fetch_set;
  uint8_t decode_set;
  uint8_t instr_set;
};

struct registers execute_instr(uint32_t instruction, struct registers regs, struct data_pipeline pipe);

void run_emulator(struct registers regs, uint8_t* memory);

void print_register_state(struct registers regs, uint8_t* memory);

#endif
