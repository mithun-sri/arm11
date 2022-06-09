#include <stdio.h>
#include <stdlib.h>

struct data_pipeline {
  uint32_t fetched;
  uint32_t decoded;
  uint8_t fetch_set;
  uint8_t decode_set;
  uint8_t instr_set;
};

void execute_instr(uint32_t instruction, struct registers regs);

void run_emulator(struct registers regs);

void print_register_state(struct registers regs);
