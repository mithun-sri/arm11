#ifndef CHOOSE_INSTRUCTION_H
#define CHOOSE_INSTRUCTION_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct data_pipeline {
  uint32_t fetched;
  uint32_t decoded;
  uint8_t fetch_set;
  uint8_t decode_set;
  uint8_t instr_set;
};

void execute_instr(uint32_t, struct *registers);

void run_emulator(struct *registers);

void print_register_state(struct *registers);

#endif
