#include <stdint.h>

#define COMMON_BITS_SHIFTED  (5 << 25) 
#define BEQ_COND_SHIFTED (0 << 28)
#define BNE_COND_SHIFTED (1 << 28)
#define BGE_COND_SHIFTED (10 << 28)
#define BLT_COND_SHIFTED (11 << 28)
#define BGT_COND_SHIFTED (12 << 28)
#define BLE_COND_SHIFTED (13 << 28)
#define B_COND_SHIFTED (14 << 28)

uint32_t beq_a(uint32_t offset);

uint32_t bne_a(uint32_t offset);

uint32_t bge_a(uint32_t offset);

uint32_t blt_a(uint32_t offset);

uint32_t bgt_a(uint32_t offset);

uint32_t ble_a(uint32_t offset);

uint32_t b_a(uint32_t offset);
