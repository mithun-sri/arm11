#include <stdio.h>
#include <string.h>
#include "emulate_architecture.h"
#include "data_processing_assemble.c"
#include "multiply_assembler.c"
#include "special_assemble.c"
#include "branch_assembler.c"

#define MAX_CHARS 0x1ff
#define OFFSET_MASK 0xffffff

// used to store labels with their associated memory addresses
typedef struct {
  char *name;
  uint32_t next_instr_addr;
} Label;

// gets the integer representation of part of an instruction
uint8_t get_val(char *str[MAX_CHARS], uint8_t pos) {
  str[pos] = str[pos] + 1;
  return atoi(str[pos]);
}

// finds the associated memory address of a label
uint32_t addr_finder(Label labels[MAX_CHARS], char str[]) {
  for (int i = 0; i < MAX_CHARS; i++) {
    if (labels[i].name == str) {
      return labels[i].next_instr_addr;
    }
  }

  printf("Label Error: Label not found");
  exit(EXIT_FAILURE);
}

// splits instructions into segments and passes in the right parameters for each function
uint8_t tokenize(char instruction[], uint8_t line_no) {
  char *str[MAX_CHARS];
  char delimit[] = " ,:";
  uint8_t i = 0;

  Label labels[MAX_CHARS];
  uint8_t numLabels = 0;
  int32_t offset;

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

  // branch
  } else if (!strcmp(str[0], "beq")) {
    uint32_t res = addr_finder(labels, str[1]);
    offset = (res - line_no) & OFFSET_MASK;
    beq_a(offset);

  } else if (!strcmp(str[0], "bne")) {
    uint32_t res = addr_finder(labels, str[1]);
    offset = (res - line_no) & OFFSET_MASK;
    bne_a(offset);

  } else if (!strcmp(str[0], "bge")) {
    uint32_t res = addr_finder(labels, str[1]);
    offset = (res - line_no) & OFFSET_MASK;
    bge_a(offset);

  } else if (!strcmp(str[0], "blt")) {
    uint32_t res = addr_finder(labels, str[1]);
    offset = (res - line_no) & OFFSET_MASK;
    blt_a(offset);

  } else if (!strcmp(str[0], "bgt")) {
    uint32_t res = addr_finder(labels, str[1]);
    offset = (res - line_no) & OFFSET_MASK;
    bgt_a(offset);

  } else if (!strcmp(str[0], "ble")) {
    uint32_t res = addr_finder(labels, str[1]);
    offset = (res - line_no) & OFFSET_MASK;
    ble_a(offset);

  } else if (!strcmp(str[0], "bal") || !strcmp(str[0], "b")) {
    uint32_t res = addr_finder(labels, str[1]);
    offset = (res - line_no) & OFFSET_MASK;
    b_a(offset);

  } else {
    Label lb;
    lb.name = str[0];
    lb.next_instr_addr = line_no;

    labels[numLabels] = lb;

    numLabels++;

    // do not increment when label found - syncs in main
    return (line_no - 1);
  }

  return line_no;
}

int main(void) {
  char instruction[511];
  uint8_t cnt;
  FILE *fPtr;

// "test.s" is the name of the test file
  fPtr = fopen("test.s", "r");

  if (fPtr == NULL) {
    printf("File Error: Unable to open file\n");
    exit(EXIT_FAILURE);
  }
  while (&free) {
    if (fgets(instruction, sizeof(instruction), fPtr) != NULL) {
      uint8_t cntSyncer = tokenize(instruction, cnt);
      cnt = cntSyncer;
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
