#ifndef DATA_PROCESSING_ASSEMBLE_H
#define DATA_PROCESSING_ASSEMBLE_H

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
#define S_BIT_MASK (1 << S_BIT_OFFSET)
#define I_BIT 0x1
#define COMMON_DATA_PROCESSING_BITS ((COND << COND_OFFSET) + (I_BIT << I_BIT_OFFSET))
#define MAX_CHARS 511 // no line is longer than 511 characters - spec

uint32_t add_a(uint8_t rn, uint8_t rd, uint8_t op2);

uint32_t sub_a(uint8_t rn, uint8_t rd, uint8_t op2);

uint32_t rsb_a(uint8_t rn, uint8_t rd, uint8_t op2);

uint32_t and_a(uint8_t rn, uint8_t rd, uint8_t op2);

uint32_t eor_a(uint8_t rn, uint8_t rd, uint8_t op2);

uint32_t orr_a(uint8_t rn, uint8_t rd, uint8_t op2);

uint32_t mov_a(uint8_t rd, uint8_t op2);

uint32_t tst_a(uint8_t rn, uint8_t op2);

uint32_t teq_a(uint8_t rn, uint8_t op2);

uint32_t cmp_a(uint8_t rn, uint8_t op2);

#endif