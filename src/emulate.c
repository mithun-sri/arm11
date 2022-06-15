#include <stdlib.h>
#include <stdio.h>
#include "emulate_architecture.h"
#include "choose_instruction.h"
#include "emulate_utilities.h"

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
  
  /*
  fseek(file, 0, SEEK_END);
  int file_size = ftell(file) / BYTES_PER_WORD;
  fseek(file, 0, SEEK_SET);
  uint32_t addr = 0;
  
  
  for (uint32_t i = 0; i < file_size; i++){
    if (fread(&addr, sizeof(uint32_t), 1, file) == 1){
      write_to_memory(memory, i * BYTES_PER_WORD, addr);
    }
  }
  */

  memory = calloc(MEMORY_CAPACITY, sizeof(uint8_t));
  fclose(file);
  run_emulator(regs, memory);

  for(int i = 0; i < NUM_GEN_PURPOSE_REGISTERS; i++){
    free(regs.gen_regs[i]);
  }
  free(memory);
  exit(EXIT_SUCCESS);
}
