#include <stdint.h>

#define MEMORY_CAPACITY 65536
#define NUM_REGISTERS 17
#define PC_INDEX 15
#define CPSR_INDEX 16
#define NUM_GEN_PURPOSE_REGISTERS 13

typedef struct {
    uint32_t *registers;
    /* TODO: Memory */
} machine_state;