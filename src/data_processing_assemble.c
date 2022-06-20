#include "data_processing_assemble.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t add_a(uint8_t rn, uint8_t rd, char* op2) {
	printf("Opcode: %s", op2);
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x4 << 21) |(rn << 16)| (rd << 12) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (rn << 16) | (0x4 << 21) |(rd << 12) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25)| (rn << 16) |(0x4 << 21) | (rd << 12) | val);
    // Immediate operand
  }

  //return (COMMON_DATA_PROCESSING_BITS + (ADD_OPCODE << OPCODE_OFFSET)
  //+ (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t sub_a(uint8_t rn, uint8_t rd, char* op2) {
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x2 << 21) |(rn << 16)| (rd << 12) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (rn << 16) | (0x2 << 21) |(rd << 12) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25)| (rn << 16) |(0x2 << 21) | (rd << 12) | val);
    // Immediate operand

  // return (COMMON_DATA_PROCESSING_BITS + (SUB_OPCODE << OPCODE_OFFSET) 
  // + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}
}

uint32_t rsb_a(uint8_t rn, uint8_t rd, char* op2) {
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x3 << 21) |(rn << 16)| (rd << 12) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (rn << 16) | (0x3 << 21) |(rd << 12) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25)| (rn << 16) |(0x3 << 21) | (rd << 12) | val);
    // Immediate operand
  }
  // return (COMMON_DATA_PROCESSING_BITS + (RSB_OPCODE << OPCODE_OFFSET) 
  // + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t and_a(uint8_t rn, uint8_t rd, char *op2) {
  printf("Opcode: %s", op2);
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) |(rn << 16)| (rd << 12) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (rn << 16) |(rd << 12) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25)| (rn << 16) | (rd << 12) | val);
    // Immediate operand
  }
  
  // return (COMMON_DATA_PROCESSING_BITS + (AND_OPCODE << OPCODE_OFFSET)
  // + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t eor_a(uint8_t rn, uint8_t rd, char* op2) {
  printf("Opcode: %s", op2);
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x1 << 21) |(rn << 16)| (rd << 12) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (rn << 16) | (0x1 << 21) |(rd << 12) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25)| (rn << 16) | (0x1 << 21) | (rd << 12) | val);
    // Immediate operand
  }
  // return (COMMON_DATA_PROCESSING_BITS + (EOR_OPCODE << OPCODE_OFFSET) 
  // + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t orr_a(uint8_t rn, uint8_t rd, char* op2) {
  printf("Opcode: %s", op2);
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0xC << 21) |(rn << 16)| (rd << 12) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (rn << 16) | (0xC << 21) |(rd << 12) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25)| (rn << 16) | (0xC << 21) | (rd << 12) | val);
    // Immediate operand
  }
  // return (COMMON_DATA_PROCESSING_BITS + (ORR_OPCODE << OPCODE_OFFSET) 
  // + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t mov_a(uint8_t rd, char* op2) { 
	printf("Mov op2: %s", op2);
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0xD << 21) | (rd << 12) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (0xD << 21) | (rd << 12) | val);
  } else {
    val = atoi(op2);
    // printf("%i\n", val);
    return ((0xE << 28) | (1 << 25) | (0xD << 21) | (rd << 12) | val);
    // Immediate operand
  }
      	// return (COMMON_DATA_PROCESSING_BITS + (MOV_OPCODE << OPCODE_OFFSET) 
  // + (rd << RD_OFFSET) + val);
}

uint32_t tst_a(uint8_t rn, char* op2) { 
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x8 << 21) | (rn << 16) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (0x8 << 21) | (rn << 16) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x8 << 21) | (rn << 16) | val);
    // Immediate operand
  }

  // return (COMMON_DATA_PROCESSING_BITS + (TST_OPCODE << OPCODE_OFFSET) 
  // + S_BIT_MASK + (rn << RN_OFFSET) + op2); 
}

uint32_t teq_a(uint8_t rn, char* op2) {
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x9 << 21) | (rn << 16) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (0x9 << 21) | (rn << 16) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0x9 << 21) | (rn << 16) | val);
    // Immediate operand
  }
  // return (COMMON_DATA_PROCESSING_BITS + (TEQ_OPCODE << OPCODE_OFFSET) 
  // + S_BIT_MASK + (rn << RN_OFFSET) + op2); 
}

uint32_t cmp_a(uint8_t rn, char* op2) {
  uint8_t val;
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0xA << 21) | (1 << 20) | (rn << 16) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return ((0xE << 28) | (0xA << 21) | (1 << 20) | (rn << 16) | val);
  } else {
    sscanf(op2, "%hhx", &val);
    return ((0xE << 28) | (1 << 25) | (0xA << 21) | (1 << 20) | (rn << 16) | val);
    // Immediate operand
  }
  // return (COMMON_DATA_PROCESSING_BITS + (CMP_OPCODE << OPCODE_OFFSET) 
  // + S_BIT_MASK + (rn << RN_OFFSET) + op2);
}
