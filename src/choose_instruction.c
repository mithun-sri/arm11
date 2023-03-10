#include "choose_instruction.h"

struct registers execute_instr(uint32_t instruction, struct registers regs) {
	uint8_t bit_27 = extract_bits(instruction, 27, 28);
  	uint8_t bit_26 = extract_bits(instruction, 26, 27);
  	uint8_t bit_22_27 = extract_bits(instruction, 22, 28);
  	uint8_t bit_4_7 = extract_bits(instruction, 4, 8);
  
  	if (bit_26 == 1) {
		regs = single_data_transfer(instruction, regs, memory);
	} else if (bit_27 == 1) {
		regs = branch(instruction, regs);
	} else {
	  if (bit_22_27 == 0 && bit_4_7 == 9){
	        regs = multiply(instruction, regs);
	  } else {
	   	regs = data_processing(instruction, regs);
	  }
 	}
  	return regs;
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

void run_emulator(struct registers regs, uint8_t* memory) {

  uint32_t instruction;
  // printf("Memory: 0x%08x\n", read_memory(&memory[*regs.pc]));
  // printf("PC: %i\n", *regs.pc);

  while (read_memory(&memory[*regs.gen_regs[PC_INDEX]]) != 0) {
     if (pipe->decode_set) {
      	instruction = pipe->decoded;
      	pipe->instr_set = 1;
     	pipe->decode_set = 0;
     }

     if (pipe->fetch_set) {
	    pipe->decoded = pipe->fetched;
	    pipe->decode_set = 1;
	    pipe->fetch_set = 0;
     }

     pipe->fetched = read_memory(&memory[*regs.gen_regs[PC_INDEX]]);
     pipe->fetch_set = 1;
     *regs.gen_regs[PC_INDEX] += 4;

     if (pipe->instr_set) {
      	   regs = execute_instr(instruction, regs);
     }
  }

  if (pipe->decode_set && pipe->fetch_set) {
	  regs = execute_instr(pipe->decoded, regs);
	  regs = execute_instr(pipe->fetched, regs);
	  *regs.gen_regs[PC_INDEX] += 8;
	  pipe->fetch_set = 0;
  }

  if (pipe->fetch_set){
    regs = execute_instr(pipe->fetched, regs);
    *regs.gen_regs[PC_INDEX] += 8;
  }
  print_register_state(regs, memory);
}

static void indent(uint32_t val, uint32_t spaces) {
    uint32_t no_spaces = spaces;
    if (val == 0) {
        no_spaces -= 1; 
    } else if (extract_bits(val, 31, 32) == 1) {
        val -= 1;
        val = ~(val);
        if (extract_bits(val, 31, 32) == 0) {
            no_spaces -= 1;
        }
    }
    while ((val > 0) && (no_spaces > 0)) {
        no_spaces -= 1;
        val /= 10;
    }
    for (int i = 0; i < no_spaces; i++) {
        printf(" ");
    }
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
	for(int i = 0; i < 13; i++) {
        printf("$%i", i);
        indent(i, 3);
        printf(": ");
        indent(*regs.gen_regs[i], 10);
		    printf("%i (0x%08x)\n", *regs.gen_regs[i], *regs.gen_regs[i]);
	}
	printf("PC  : ");
  	indent(*regs.gen_regs[PC_INDEX], 10);
	printf("%i (0x%08x)\n", *regs.gen_regs[PC_INDEX], *regs.gen_regs[PC_INDEX]);
	printf("CPSR: ");
  	indent(regs.cpsr, 10);
  	printf("%i (0x%08x)\n", regs.cpsr, regs.cpsr);
  	printf("Non-zero memory:\n");
  	display_memory(memory);
}
