#include <stdio.h>
#include <string.h>
#include "emulate_architecture.h"
#include "data_processing.h"

#define MOV_OPCODE 0xd
#define TST_OPCODE 0x8
#define TEQ_OPCODE 0x9
#define CMP_OPCODE 0xa
#define AND_OPCODE 0x0
#define EOR_OPCODE 0x1
#define SUB_OPCODE 0x2
#define RSB_OPCODE 0x3
#define ADD_OPCODE 0x4
#define ORR_OPCODE 0xc
#define COND 0xe
#define S_BIT_MASK 1 << S_BIT_OFFSET
// not implementing shifted register
#define I_BIT 0x1
#define COMMON_DATA_PROCESSING_BITS (COND << COND_OFFSET + I_BIT << I_BIT_OFFSET)
// no line is longer than 511 characters - spec
#define MAX_CHARS 511

uint32_t add_a(uint32_t rn, uint32_t rd, Operand2 op2) {
  return (COMMON_DATA_PROCESSING_BITS \ 
    + (ADD_OPCODE << OPCODE_OFFSET) + (rn << RN_OFFSET) + (rd << RD_OFFSET) \ 
    + op2.value);
}

uint32_t sub_a(uint32_t rn, uint32_t rd, Operand2 op2) {
  return (COMMON_DATA_PROCESSING_BITS \ 
    + (SUB_OPCODE << OPCODE_OFFSET) + (rn << RN_OFFSET) + (rd << RD_OFFSET) \ 
    + op2.value);
}

uint32_t rsb_a(uint32_t rn, uint32_t rd, Operand2 op2) {
  return (COMMON_DATA_PROCESSING_BITS \ 
    + (RSB_OPCODE << OPCODE_OFFSET) + (rn << RN_OFFSET) + (rd << RD_OFFSET) \ 
    + op2.value);
}

uint32_t and_a(uint32_t rn, uint32_t rd, Operand2 op2) {
  return (COMMON_DATA_PROCESSING_BITS \ 
    + (AND_OPCODE << OPCODE_OFFSET) + (rn << RN_OFFSET) + (rd << RD_OFFSET) \ 
    + op2.value);
}

uint32_t eor_a(uint32_t rn, uint32_t rd, Operand2 op2) {
  return (COMMON_DATA_PROCESSING_BITS \ 
    + (AND_OPCODE << OPCODE_OFFSET) + (rn << RN_OFFSET) + (rd << RD_OFFSET) \ 
    + op2.value);
}

uint32_t orr_a(uint32_t rn, uint32_t rd, Operand2 op2) {
  return (COMMON_DATA_PROCESSING_BITS \ 
    + (AND_OPCODE << OPCODE_OFFSET) + (rn << RN_OFFSET) + (rd << RD_OFFSET) \ 
    + op2.value);
}

int mov_a(uint8_t* rd, Operand2 op2) { 
  return (COMMON_DATA_PROCESSING_BITS \
    + (MOV_OPCODE << OPCODE_OFFSET) + (((long int) rd) << RD_OFFSET) \
    + (op2.value));
}

int tst_a(uint32_t rn, Operand2 op2) { 
  return (COMMON_DATA_PROCESSING_BITS \
    + (TST_OPCODE << OPCODE_OFFSET) + S_BIT_MASK \
    + (rn << RN_OFFSET) + (op2.value)); 
}

int teq_a(Opcode opcode, uint32_t rn, Operand2 op2) {
  return (COMMON_DATA_PROCESSING_BITS \
    + (TEQ_OPCODE << OPCODE_OFFSET) + S_BIT_MASK \
    + (rn << RN_OFFSET) + (op2.value)); 
}

int cmp_a(Opcode opcode, uint32_t rn, Operand2 op2) {
  uint8_t s_bit = 1;
  return (COMMON_DATA_PROCESSING_BITS \
    + (CMP_OPCODE << OPCODE_OFFSET) + S_BIT_MASK \
    + (rn << RN_OFFSET) + (op2.value));
}
