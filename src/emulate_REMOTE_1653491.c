#include <stdlib.h>
#include <stdio.h>
#include "emulate.h"
#define BYTES_PER_WORD 4

int main(int argc, char **argv) {
  FILE *fPtr;
  if ((fPtr = fopen(argv[1], "rb")) == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  /* Initialise memory and registers to 0 */
  struct registers regs;
  *regs.gen_regs = calloc(NUM_GEN_PURPOSE_REGISTERS, sizeof(uint32_t));
  regs.cpsr = 0;
  regs.pc = 0;
  uint8_t *memory = calloc(MEMORY_CAPACITY, sizeof(uint8_t));

  /* Load instructions into memory */
    fseek(fPtr, 0, SEEK_SET);
    uint8_t *memory = calloc(MAX_SPACE, sizeof(uint8_t));
    size_t file_size = fread(memory, MAX_SPACE, 1, fPtr) / BYTES_PER_WORD;
    fclose(fPtr); 

  for (uint32_t i = 0; i < file_size; i++){
  }

  /* Begin execution */
  exit(EXIT_SUCCESS)
}
