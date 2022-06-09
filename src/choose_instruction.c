#include "choose_instruction.h"

void execute_instr(uint32_t instruction, struct registers regs) {
  uint8_t bit_27 = (instruction >> 27) & 1;
  uint8_t bit_26 = (instruction >> 26) & 1;
  uint8_t bit_22_27 = (instruction >> 22) & ((1 << 5));
  uint8_t bit_4_7 = (instruction >> 4) & ((1 << 3));

  if (bit_27 == 1) {
	  branch(instruction, regs);
	  pipe.decode_set = 0;
	  pipe.fetch_set = 0;
  }

  if (bit_26 == 1) {
	  single_data_transfer(instruction, regs);
  }

  else {
	  if (bit_22_27 == 0 && bit_4_7 == 9) {
	    multiply(instruction, regs);
	  }
  
	  else {
	    data_processing(instruction, regs);
	  }
  }
}


void run_emulator(struct registers regs) {

  uint32_t instruction;

  struct data_pipeline pipe;
  pipe.fetch_set = 0;
  pipe.decode_set = 0;
  pipe.instr_set = 0;

  while (*(regs.pc) != 0) {

    if (pipe.decode_set) {
      instruction = pipe.decoded;
      pipe.instr_set = 1;
      pipe.decode_set = 0;
    }
      
    if (pipe.fetch_set) {
	    pipe.decoded = pipe.fetched;
	    pipe.decode_set = 1;
	    pipe.fetch_set = 0;
    }
    
    pipe.fetched = *(regs.pc);
    regs.pc += 4;

    if (pipe.instr_set) {
      execute_instr(instruction, regs);
    }
  }

  if (decode_set) {
    execute_instr(decoded, regs);
  }

  if (fetch_set) {
    execute_instr(fetched, regs);
  }

}

void print_register_state(struct registers regs) {
  for(int i = 0; i < 13; i++) {
    printf("r%i: %lf\n", i+1, regs.general[i]);
  }
  printf("cspr: %lf\n", regs.cspr);
  printf("pc: %lf\n", regs.pc);
}
    





    
 



