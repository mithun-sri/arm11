#include <stdint.h>

#define COMMON_BITS_SHIFTED  (5 << 25)  // 101 in bits 25 to 27 inclusive
#define BEQ_COND_SHIFTED (0 << 28)  // 0000 in bits 28 to 31 inclusive
#define BNE_COND_SHIFTED (1 << 28)  // 0001 in bits 28 to 31 inclusive
#define BGE_COND_SHIFTED (10 << 28)   // 1010 in bits 28 to 31 inclusive
#define BLT_COND_SHIFTED (11 << 28)   // 1011 in bits 28 to 31 inclusive
#define BGT_COND_SHIFTED (12 << 28)   // 1100 in bits 28 to 31 inclusive
#define BLE_COND_SHIFTED (13 << 28)   // 1101 in bits 28 to 31 inclusive
#define B_COND_SHIFTED (14 << 28)   // 1110 in bits 28 to 31 inclusive

uint32_t beq_a(uint32_t offset);

uint32_t bne_a(uint32_t offset);

uint32_t bge_a(uint32_t offset);

uint32_t blt_a(uint32_t offset);

uint32_t bgt_a(uint32_t offset);

uint32_t ble_a(uint32_t offset);

uint32_t b_a(uint32_t offset);


