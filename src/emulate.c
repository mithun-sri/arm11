#include <stdlib.h>
#include <stdio.h>
#include "emulate_architecture.h"
#include "choose_instruction.h"

int main(int argc, char **argv) {
	FILE *file;
	if ((file = fopen(argv[1], "rb")) == NULL){
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	struct registers regs = {{calloc(NUM_GEN_PURPOSE_REGISTERS, sizeof(uint32_t))}, calloc(1, sizeof(uint32_t)), 0};
	for (int i = 0; i < NUM_GEN_PURPOSE_REGISTERS; i++){
		regs.gen_regs[i] = calloc(1, sizeof(uint32_t));
	}
  	memory =(uint8_t *) calloc(MEMORY_CAPACITY, sizeof(uint8_t));

  	fread((int8_t *) memory, BYTES_PER_WORD, MAX_INSTR_COUNT, file);
  	fclose(file);
//	free(regs.gen_regs);
	free(memory);
	run_emulator(regs, memory);
	for (int i = 0; i < NUM_GEN_PURPOSE_REGISTERS; i++){
		free(regs.gen_regs[i]);
	}
	exit(EXIT_SUCCESS);
}
