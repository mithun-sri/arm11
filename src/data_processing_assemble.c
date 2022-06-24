#include "data_processing_assemble.h"
#include "data_processing.h"
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
    return (COND_CODE | (1 << I_BIT_OFFSET) | (0x4 << OPCODE_OFFSET) |(rn << RN_OFFSET)| (rd << RD_OFFSET) | val);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%hhx", &val);
      return (COND_CODE | (rn << RN_OFFSET) | (0x4 << OPCODE_OFFSET) |(rd << RD_OFFSET) | val);
  } else {
    // Immediate operand
    sscanf(op2, "%hhx", &val);
    return (COND_CODE | (1 << I_BIT_OFFSET)| (rn << RN_OFFSET) |(0x4 << OPCODE_OFFSET) | (rd << RD_OFFSET) | val);
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

static uint32_t convertOperand(uint32_t op2_32bit) {
    uint32_t rot;
    uint32_t result = op2_32bit;
    int condition = 1;
    int rotate_value = 0;
    if (op2_32bit != 0){
      while(condition) {
        //check bit0 and bit1
        int bit0 = (op2_32bit & 1);
        int bit1 = ((op2_32bit & 2)>>1);
        //stop the while loop either bit0 or bit1 is 1
        if((bit0) || (bit1)) {
            condition = 0;
        }
        if(condition) {
            //shift value = n -> shift 2n times
            op2_32bit = op2_32bit >> 2;
            rotate_value++;
        }
    }

    if(0 != rotate_value) {
        //count rotate backward (1 round is 16)
        rot = (uint32_t)(16 - rotate_value);
        //rot is the shift value which starts at bit 8
        result = op2_32bit | (rot << 8);
    }
      return result;
    }
    return 0;
}

uint32_t mov_a(uint8_t rd, char* op2) { 
	printf("Mov op2: %s", op2);
  uint32_t val;
  // uint32_t res = val;
  
  printf("%s\n", op2);
  if (strncmp(op2, "0x", 2) == 0){
    // Hex operand
	  sscanf((op2 + 2), "%x", &val);
    printf("VAL: %x\n", val);
    uint32_t value;
    if (val > 255) {
      value = convertOperand(val);
    } else {
      value = val;
    }
    return ((0xE << 28) | (1 << 25) | (0xD << 21) | (rd << 12) | value);
  } else if (strncmp(op2, "r", 1) == 0) {
    // Register operand
      sscanf((op2 + 1), "%x", &val);
      return ((0xE << 28) | (0xD << 21) | (rd << 12) | val);
  } else {
    printf("%s\n", op2);
    val = atoll(op2);
    printf("%x\n", val);
    uint32_t value;
    if (val > 255) {
      value = convertOperand(val);
    } else {
      value = val;
    }
    printf("%x\n", value);
    return ((0xE << 28) | (1 << 25) | (0xD << 21) | (rd << 12) | value);
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
