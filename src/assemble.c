/*
DATA PROCESSING (ASSEMBLER)

-Types of instructions:
    1. compute results: and, eor, sub, rsb, add, orr - TK
        Syntax: <opcode> Rd, Rn, <Operand2>
    2. single operand: mov - SB
        Syntax: mov Rd, <Operand2>
    3. Do not compute results + set CPSR flags: tst, teq, cmp - SB
        Syntax: <opcode> Rn, <Operand2>

-Rd, Rn, Rm:
    Represent registers, usually written r0, r1, r2,...

-Operand2:
    Represents operand: expression <#expression>, shifted register Rm{,<shift>} - optional

-<#expression>:
    Numeric constant: Attempt to generate 8-bit immediate value (see Data Processing for emulator), if not possible then throw error
    Can be represented in decimal or hexadecimal (prefix with 0x)

Q - How do you generate rotate value? Is it ok to just say rotate == 0 each time?

-<shift>: see Data Processing shifts for emulator
    Form:
        1. <shiftname> <register>
        2. <shiftname> <#expression>
    <shiftname> can be asr(algebraic shift right), lsl(logical shift left), lsr (logical shift right), ror(rotate right)

-Summary of binary format for Data Processing in Emulator:
    Opcode  Mnemonic
    0000    and
    0001    eor
    0010    sub
    0011    rsb
    0100    add
    1100    orr
    1101    mov
    1000    tst
    1001    teq
    1010    cmp

    31   28 27     25 24    21  20 1916 1512 11        0
    ----------------------------------------------------
    | Cond | 0 0 | I | OpCode | S | Rn | Rd | Operand2 |
    ----------------------------------------------------

    For tst, teq, cmp: S == 1; else: S == 0;
    For all instructions: Cond == 1110 -> always condition;
*/

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
// not implementing shifted register
#define I_BIT 0x1
#define COMMON_DATA_PROCESSING_BITS ((COND << COND_OFFSET) + (I_BIT << I_BIT_OFFSET))
// no line is longer than 511 characters - spec
#define MAX_CHARS 511

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
  return (COMMON_DATA_PROCESSING_BITS + (AND_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t orr_a(uint8_t rn, uint8_t rd, uint8_t op2) {
  return (COMMON_DATA_PROCESSING_BITS + (AND_OPCODE << OPCODE_OFFSET) 
  + (rn << RN_OFFSET) + (rd << RD_OFFSET) + op2);
}

uint32_t mov_a(uint8_t rd, uint8_t op2) { 
  return (COMMON_DATA_PROCESSING_BITS + (MOV_OPCODE << OPCODE_OFFSET) 
  + (((long int) rd) << RD_OFFSET) + op2);
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
  uint8_t s_bit = 1;
  return (COMMON_DATA_PROCESSING_BITS + (CMP_OPCODE << OPCODE_OFFSET) 
  + S_BIT_MASK + (rn << RN_OFFSET) + op2);
}

uint8_t get_val(char *str[MAX_CHARS], uint8_t pos) {
  str[pos] = str[pos] + 1;
  return atoi(str[pos]);
}

void tokenize(char instruction[]) {
  char *str[MAX_CHARS];
  char delimit[] = " ,";
  int i = 0;
  
  str[i] = strtok(instruction, delimit);
  while(str[i] != NULL) {
    i++;
    str[i] = strtok(NULL, delimit);
  }

  if (!strcmp(str[0], "mov")) {
  //   // remove r
  //   uint8_t rd = get_val(str, 1);
  //   printf("mm: %d\n", rd);

  //   // remove #
  //   uint8_t op2 = get_val(str, 2);
  //   printf("mmm: %d\n", op2);

  // printf("%d\n", mov_a(get_val(str, 1), get_val(str, 2)));

    mov_a(get_val(str, 1), get_val(str, 2));
  } else if (!strcmp(str[0], "add")) {
    // remove r from rd
    str[1] = str[1] + 1;
    uint8_t rd = atoi(str[1]);
    printf("a1: %d\n", rd);

    // remove r from rn
    str[2] = str[2] + 1;
    uint8_t rn = atoi(str[2]);
    printf("a: %d\n", rn);
    
    // remove # from op2
    str[3] = str[3] + 1;
    uint8_t op2 = atoi(str[3]);
    printf("a: %d\n", op2);

    printf("a: %d\n", add_a(rn, rd, op2));
  }
}

int main(void) {
  char instruction[511];
  FILE *fPtr;

// "test.txt" is the name of the test file
  fPtr = fopen("test.txt", "r");

  if (fPtr == NULL) {
    printf("File error: Unable to open file");
    exit(EXIT_FAILURE);
  }

  if (fgets(instruction, sizeof(instruction), fPtr) != NULL) {
    tokenize(instruction);
  } else {
    printf("File Error: Unable to read file");
    exit(EXIT_FAILURE);
  }
}
