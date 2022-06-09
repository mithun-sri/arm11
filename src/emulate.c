#include "emulate_architecture.h"
#include "choose_instruction.h"

uint8_t *memory;

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
  memory = calloc(MEMORY_CAPACITY, sizeof(uint8_t));

  /* Load instruction */
  fread((int8_t *) memory, BYTES_PER_WORD, MAX_INSTR_COUNT, file);
  fclose(file);

  /* Begin execution */
  run_emulator(regs);
  printf("Demo passed");
  
  exit(EXIT_SUCCESS);
}
