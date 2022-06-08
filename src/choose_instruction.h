#include <stdio.h>
#include <stdlib.h>

struct data_pipeline {
  uint32_t fetched;
  uint32_t decoded;
  uint8_t fetch_set;
  uint8_t decode_set;
  uint8_t instr_set;
};

void run_emulator(struct registers regs);
