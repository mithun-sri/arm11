#include "data_processing_assemble.h"


uint32_t add_a(uint8_t rn, uint8_t rd, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (ADD_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t sub_a(uint8_t rn, uint8_t rd, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (SUB_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t rsb_a(uint8_t rn, uint8_t rd, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (RSB_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t and_a(uint8_t rn, uint8_t rd, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (AND_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t eor_a(uint8_t rn, uint8_t rd, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (EOR_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t orr_a(uint8_t rn, uint8_t rd, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (ORR_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t mov_a(uint8_t rd, uint8_t op2) { 
  return (COMMON_DATA_PROCESSING_BITS + (MOV_OPCODE << OPCODE_OFFSET) 
  + (rd << RD_OFFSET) + op2);
}

uint32_t tst_a(uint8_t rn, uint8_t op2) { 
  return (COMMON_DATA_PROCESSING_BITS + (TST_OPCODE << OPCODE_OFFSET) 
  + S_BIT_MASK + (rn << RN_OFFSET) + op2); 
}

uint32_t teq_a(uint8_t rn, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (TEQ_OPCODE << OPCODE_OFFSET) 
  + S_BIT_MASK + (rn << RN_OFFSET) + op2); 
}

uint32_t cmp_a(uint8_t rn, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (CMP_OPCODE << OPCODE_OFFSET) 
  + S_BIT_MASK + (rn << RN_OFFSET) + op2);
}
