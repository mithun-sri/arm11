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
#include "data_processing_assemble.c"
#include "multiply_assembler.c"
#include "special_assemble.c"

#define MAX_CHARS 511

typedef struct {
  char *name;
  uint32_t next_instr_addr;
} Label;

uint8_t get_val(char *str[MAX_CHARS], uint8_t pos) {
  str[pos] = str[pos] + 1;
  return atoi(str[pos]);
}

uint8_t tokenize(char instruction[], uint8_t line_no) {
  char *str[MAX_CHARS];
  char delimit[] = " ,";
  int i = 0;
  
  str[i] = strtok(instruction, delimit);
  while(str[i] != NULL) {
    i++;
    str[i] = strtok(NULL, delimit);
  }

  // data_processing
  if (!strcmp(str[0], "mov")) {
    mov_a(get_val(str, 1), get_val(str, 2));

  } else if (!strcmp(str[0], "add")) {
    add_a(get_val(str, 2), get_val(str, 1), get_val(str, 3));

  } else if (!strcmp(str[0], "sub")) {
    sub_a(get_val(str, 2), get_val(str, 1), get_val(str, 3));

  } else if (!strcmp(str[0], "rsb")) {
    rsb_a(get_val(str, 2), get_val(str, 1), get_val(str, 3));

  } else if (!strcmp(str[0], "and")) {
    and_a(get_val(str, 2), get_val(str, 1), get_val(str, 3));

  } else if (!strcmp(str[0], "eor")) {
    eor_a(get_val(str, 2), get_val(str, 1), get_val(str, 3));

  } else if (!strcmp(str[0], "orr")) {
    orr_a(get_val(str, 2), get_val(str, 1), get_val(str, 3));

  } else if (!strcmp(str[0], "tst")) {
    tst_a(get_val(str, 1), get_val(str, 2));

  } else if (!strcmp(str[0], "teq")) {
    teq_a(get_val(str, 1), get_val(str, 2));

  } else if (!strcmp(str[0], "cmp")) {
    cmp_a(get_val(str, 1), get_val(str, 2));

// multiply
  } else if (!strcmp(str[0], "mul")) {
    mul_a(get_val(str, 1), get_val(str, 2), get_val(str, 3));

  } else if (!strcmp(str[0], "mla")) {
    mla_a(get_val(str, 1), get_val(str, 2), get_val(str, 3), get_val(str, 4));

  // single data transfer -- wait
  } else if (!strcmp(str[0], "ldr")) {
    // check parameter order
    
  } else if (!strcmp(str[0], "str")) {
    // check parameter order

  // special
  } else if (!strcmp(str[0], "andeq")) {
    andeq_a();

  } else if (!strcmp(str[0], "lsl")) {
    lsl_a(get_val(str, 1), get_val(str, 2));

  } else {
    Label lb;
    lb.name = str[0];
    lb.next_instr_addr = line_no;

    // do not increment when label found - syncs in main
    // printf("label : %d\n", line_no);
    return (line_no - 1);
  }

  // printf("current cnt : %d\n", line_no);
  return line_no;
}

int main(void) {
  char instruction[511];
  uint8_t cnt;
  FILE *fPtr;

// "test.s" is the name of the test file
  fPtr = fopen("test.s", "r");

  if (fPtr == NULL) {
    printf("File error: Unable to open file\n");
    exit(EXIT_FAILURE);
  }
  while (&free) {
    if (fgets(instruction, sizeof(instruction), fPtr) != NULL) {
      // printf("%s\n", instruction);
      uint8_t cntSyncer = tokenize(instruction, cnt);
      cnt = cntSyncer;
      // printf("\n---cnt after label return : %d\n\n", cnt);
      cnt++;
    } else {
      if (feof(fPtr)) {
        exit(EXIT_SUCCESS);
      }
      printf("File Error: Unable to read file\n");
      exit(EXIT_FAILURE);
    }
  }
}
