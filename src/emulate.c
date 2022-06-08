#include <stdlib.h>
#include <stdio.h>
#include "emulate.h"
#define BYTES_PER_WORD 4

int main(int argc, char **argv) {
  FILE *file;
  if ((file = fopen(argv[1], "rb")) == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  /* Initialise memory and registers to 0 */
  struct registers regs;
  *regs.gen_regs = calloc(NUM_GEN_PURPOSE_REGISTERS, sizeof(uint32_t));
  regs.cpsr = 0;
  regs.pc = 0;
  *memory = calloc(MEMORY_CAPACITY, sizeof(uint8_t));

  /* Load instructions into memory */
  fseek(file, 0, SEEK_END);
  uint32_t file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  for (uint32_t i = 0; i < file_size; i++){
      
  }

  fclose(file);

  /* Begin execution */
  return EXIT_SUCCESS;
}