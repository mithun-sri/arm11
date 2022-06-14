#include "emulate_architecture.h"
#include "choose_instruction.h"

int main(int argc, char **argv) {
  FILE *file;
  if ((file = fopen(argv[1], "rb")) == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  /* Initialise memory and registers to 0 */
  printf("Demo passed");
  struct registers regs = {{ calloc(NUM_GEN_PURPOSE_REGISTERS, sizeof(uint32_t)), 0, 0 }};
  memory = calloc(MEMORY_CAPACITY, sizeof(uint8_t));
  *(registers.pc) = &memory;
  

  /* Load instruction */
  fread((int8_t *) memory, BYTES_PER_WORD, MAX_INSTR_COUNT, file);
  fclose(file);

  /* Begin execution */
  run_emulator(regs);
  
  exit(EXIT_SUCCESS);
}
