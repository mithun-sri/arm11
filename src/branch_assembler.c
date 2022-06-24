#include "branch_assembler.h"


uint32_t beq_a(uint32_t offset) {
  return (COMMON_BITS_SHIFTED + BEQ_COND_SHIFTED + offset);
}

uint32_t bne_a(uint32_t offset) {
  return (COMMON_BITS_SHIFTED + BNE_COND_SHIFTED + offset);
}

uint32_t bge_a(uint32_t offset) {
  return (COMMON_BITS_SHIFTED + BGE_COND_SHIFTED + offset);
}

uint32_t blt_a(uint32_t offset) {
  return (COMMON_BITS_SHIFTED + BLT_COND_SHIFTED + offset);
}

uint32_t bgt_a(uint32_t offset) {
  return (COMMON_BITS_SHIFTED + BGT_COND_SHIFTED + offset);
}

uint32_t ble_a(uint32_t offset) {
  return (COMMON_BITS_SHIFTED + BLE_COND_SHIFTED + offset);
}

uint32_t b_a(uint32_t offset) {
  return (COMMON_BITS_SHIFTED + B_COND_SHIFTED + offset);
}