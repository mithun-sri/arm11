#include "multiply_assembler.h"

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


uint32_t mla_a(uint8_t Rd, uint8_t Rm, uint8_t Rs, uint8_t Rn) {
  return (MULTIPLY_COMMON_BITS + Rm + (Rs << RS_SHIFT) + (Rn << RN_SHIFT) + (Rd << RD_SHIFT) + (S_BIT << S_BIT_SHIFT) + (1 << A_BIT_SHIFT) + (MUL_COND_CODE << COND_SHIFT));
}


uint32_t mul_a(uint8_t Rd, uint8_t Rm, uint8_t Rs) {
 return (MULTIPLY_COMMON_BITS + Rm + (Rs << RS_SHIFT) + (Rd << RD_SHIFT) + (S_BIT << S_BIT_SHIFT) + (MUL_COND_CODE << COND_SHIFT));
}


// auto casting from uint8 to 32 when shifting applied?
