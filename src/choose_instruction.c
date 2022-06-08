#include "choose_instruction.h"

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


    if (pipe.instr_set) {

      uint8_t bit_27 = (instruction >> 27) & 1;
      uint8_t bit_26 = (instruction >> 26) & 1;
      uint8_t bit_22_27 = (instruction >> 22) & ((1 << 5));
      uint8_t bit_4_7 = (instruction >> 4) & ((1 << 3));

      if (bit_27 == 1) {
	branch(instruction);
	pipe.decode_set = 0;
	pipe.fetch_set = 0;
      }

      if (bit_26 == 1) {
	single_data_transfer(instruction);
      }

      else {
	if (bit_22_27 == 0 && bit_4_7 == 9) {
	  multiply(instruction);
	}
  
	else {
	  data_processing(instruction);
	}
      }
    }
  }
}
    





    
 



