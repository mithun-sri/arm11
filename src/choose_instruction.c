#include "choose_instruction.h"


void execute_instr(uint32_t instruction, struct registers regs, struct data_pipeline pipe) {
  uint8_t bit_27 = (instruction >> 27) & 1;
  uint8_t bit_26 = (instruction >> 26) & 1;
  uint8_t bit_22_27 = (instruction >> 22) & ((1 << 5));
  uint8_t bit_4_7 = (instruction >> 4) & ((1 << 3));

  if (bit_27 == 1) {
	  printf("Branch instruction");
	  // branch(instruction, regs);
	  pipe.decode_set = 0;
	  pipe.fetch_set = 0;
  }

  if (bit_26 == 1) {
	  printf("Single data transfer instruction");
	  // single_data_transfer(instruction, regs);
  }

  else {
	  if (bit_22_27 == 0 && bit_4_7 == 9) {
		printf("Multiply instruction");
	    	// multiply(instruction, regs);
	  }
  
	  else {
		  printf("Data processing instruction");
	   	 // data_processing(instruction, regs);
	  }
  }
}


void run_emulator(struct registers regs, uint8_t* memory) {

  /*uint32_t instruction;

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
      execute_instr(instruction, regs, pipe);
    }
  }

  if (pipe.decode_set) {
    execute_instr(pipe.decoded, regs, pipe);
  }

  if (pipe.fetch_set) {
    execute_instr(pipe.fetched, regs, pipe);
  }*/
  print_register_state(regs, memory);

}

void print_register_state(struct registers regs, uint8_t* memory) {
	printf("Registers:\n");
	for(int i = 0; i < 10; i++) {
		printf("$%i  :          %i (0x%08x)\n", i, *regs.gen_regs[i], *regs.gen_regs[i]);
	}
  for (int i = 10; i < 13; i++){
    printf("$%i :          %i (0x%08x)\n", i, *regs.gen_regs[i], *regs.gen_regs[i]);
  }
	printf("PC  :          %i (0x%08x)\n", *regs.pc, *regs.pc);
	printf("CPSR:          %i (0x%08x)\n", regs.cpsr, regs.cpsr);
	printf("Non-zero memory:\n");
	for (int i = 0; i < MEMORY_CAPACITY; i = i + BYTES_PER_WORD){
    if (memory[i] != 0){
      printf("0x%08x: 0x", i);
      printf("%08x\n", memory[i]);
    }
	}
}
