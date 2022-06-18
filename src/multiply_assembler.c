#include "multiply_assembler.h"

uint32_t mla_a(uint8_t Rd, uint8_t Rm, uint8_t Rs, uint8_t Rn) {
  return (MULTIPLY_COMMON_BITS + Rm + (Rs << RS_SHIFT) + (Rn << RN_SHIFT) 
  + (Rd << RD_SHIFT) + (S_BIT << S_BIT_SHIFT) + (1 << A_BIT_SHIFT) 
  + (MUL_COND_CODE << COND_SHIFT));
}

uint32_t mul_a(uint8_t Rd, uint8_t Rm, uint8_t Rs) {
 return (MULTIPLY_COMMON_BITS + Rm + (Rs << RS_SHIFT) + (Rd << RD_SHIFT) 
 + (S_BIT << S_BIT_SHIFT) + (MUL_COND_CODE << COND_SHIFT));
}
