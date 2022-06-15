#include "choose_instruction.h"


void execute_instr(uint32_t instruction, struct registers regs, struct data_pipeline pipe) {
  uint8_t bit_27 = extract_bits(instruction, 27, 28);
  uint8_t bit_26 = extract_bits(instruction, 26, 27);
  uint8_t bit_22_27 = extract_bits(instruction, 22, 28);
  uint8_t bit_4_7 = extract_bits(instruction, 4, 8);

  if (bit_27 == 1) {
	  printf("Branch instruction\n");
	  // branch(instruction, regs);
	  pipe.decode_set = 0;
	  pipe.fetch_set = 0;
  } else if (bit_26 == 1) {
	  printf("Single data transfer instruction\n");
	  // single_data_transfer(instruction, regs);
  } else {
	  if (bit_22_27 == 0 && bit_4_7 == 9) {
		printf("Multiply instruction");
	    	// multiply(instruction, regs);
	  } else {
		  printf("Data processing instruction\n");
	   	// data_processing(instruction, regs);
	  }
  }
}



void run_emulator(struct registers regs, uint8_t* memory) {

  uint32_t instruction;
  struct data_pipeline pipe;
  pipe.fetch_set = 0;
  pipe.decode_set = 0;
  pipe.instr_set = 0;

  while (memory[*regs.pc] != 0) {
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
    
    pipe.fetched = memory[*(regs.pc)];
    pipe.fetch_set = 1;
    *regs.pc += 4;

    if (pipe.instr_set) {
      execute_instr(instruction, regs, pipe);
    }
  }

  if (pipe.decode_set) {
    execute_instr(pipe.decoded, regs, pipe);
  }

  if (pipe.fetch_set) {
    execute_instr(pipe.fetched, regs, pipe);
  }
  
  print_register_state(regs, memory);

}

static uint32_t read_memory(uint8_t* address){
  uint32_t result = 0;
  uint8_t *ptr = address;
  for (uint8_t j = 0; j < BYTES_PER_WORD; j++) {
    result |= ((*ptr) << (j * 8));
    ptr++; 
  }
  return result;
}

static void display_memory(uint8_t* memory){
  for (int i = 0; i < MEMORY_CAPACITY; i = i + BYTES_PER_WORD){
    uint32_t result = read_memory(&memory[i]);
    if (result != 0){
      printf("0x%08x: 0x", i);
      for (uint32_t j = 0; j < BYTES_PER_WORD; j++) {
        uint8_t endian_value = (uint8_t) extract_bits(result, j * 8, (j + 1) * 8);
        printf("%02x", endian_value); 
      }
      printf("\n");
    }
  }
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
  display_memory(memory);
}
