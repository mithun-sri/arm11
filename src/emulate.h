#include <stdint.h>

#define MEMORY_CAPACITY 65536
#define NUM_REGISTERS 17
#define PC_INDEX 15
#define CPSR_INDEX 16
#define NUM_GEN_PURPOSE_REGISTERS 13
#define BYTES_PER_WORD 4

struct registers {
	uint32_t *gen_regs[NUM_GEN_PURPOSE_REGISTERS];
	uint32_t *pc;
	uint32_t cpsr;
};

uint8_t *memory;

