#include <stdlib.h>
#include <stdio.h>
#include "emulate_architecture.h"
#include "choose_instruction.h"
#include "emulate_utilities.h"
#define BYTE_SIZE 8

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
  
  fseek(file, 0, SEEK_END);
  int file_size = ftell(file) / BYTES_PER_WORD;
  fseek(file, 0, SEEK_SET);
  uint32_t addr = 0;

  memory = calloc(MEMORY_CAPACITY, sizeof(uint8_t));

  for (uint32_t k = 0; k < file_size; k++){
    uint32_t value = 0;
    if (fread(&value, sizeof(uint32_t), 1, file) == 1){
      uint8_t *ptr = &memory[k * BYTES_PER_WORD];
      for (uint8_t i = 0; i < BYTES_PER_WORD; i++){
        *ptr = (uint8_t) extract_bits(value, i * BYTE_SIZE, (i + 1) * BYTE_SIZE);
//	printf("0x%08x\n", extract_bits(value, i * BYTE_SIZE, (i + 1) * BYTE_SIZE));
        ptr++;
      }
    }
  }
  
  fclose(file);
  run_emulator(regs, memory);

  for(int i = 0; i < NUM_GEN_PURPOSE_REGISTERS; i++){
    free(regs.gen_regs[i]);
  }
  free(memory);
  exit(EXIT_SUCCESS);
}
