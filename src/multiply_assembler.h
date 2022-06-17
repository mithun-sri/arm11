#include <stdint.h>


#define MULTIPLY_COMMON_BITS (9 << 4)  // the 1001 in bits 4-7 are common to both multiply instructions
#define RS_SHIFT 8
#define RN_SHIFT 12
#define RD_SHIFT 16
#define S_BIT 0
#define S_BIT_SHIFT 20
#define A_BIT_SHIFT 21
#define MUL_COND_CODE 14
#define COND_SHIFT 28

uint32_t mla_a(uint8_t Rd, uint8_t Rm, uint8_t Rs, uint8_t Rn);

uint32_t mul_a(uint8_t Rd, uint8_t Rm, uint8_t Rs);
