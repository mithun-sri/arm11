#include <stdlib.h>
#include <stdio.h> 

#define BYTES_PER_WORD 4
#define MAX_INSTR_COUNT 16384
#define MEMORY_CAPACITY 65536
#define NUM_REGISTERS 17
#define PC_INDEX 15
#define CPSR_INDEX 16
#define NUM_GEN_PURPOSE_REGISTERS 13
#define BYTES_PER_WORD 4

struct registers {
	uint32_t *gen_regs[NUM_GEN_PURPOSE_REGISTERS];
	uint32_t pc;
	uint32_t cpsr;
};

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
  *memory = calloc(MEMORY_CAPACITY, sizeof(uint8_t));

  /* Load instruction */
  fread(*memory, BYTES_PER_WORD, MAX_INSTR_COUNT, file);
  fclose(file);

  /* Begin execution */
  exit(EXIT_SUCCESS)
}
