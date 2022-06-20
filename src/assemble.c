#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data_processing_assemble.h"
#include "multiply_assembler.h"
#include "special_assemble.h"
#include "branch_assembler.h"
#include "assemble_utilities.h"
#include "single_data_transfer_assemble.h"

#define MAX_CHARS 0x1ff
#define OFFSET_MASK 0xffffff

// used to store labels with their associated memory addresses
typedef struct {
  char *name;
  uint32_t next_instr_addr;
} Label;

typedef struct {
  int line_no;
  char *res;
} Result;

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

// checks if str2 starts with str1
uint8_t startsWith(char *str1, char *str2) {
  return !strncmp(str2, str1, strlen(str1));
}

// splits instructions into segments and passes in the right parameters for each function
Result tokenize(char instruction[], int line_no) {
  char *str[MAX_CHARS];
  char delimit[] = " ,:";
  uint8_t i = 0;
  Result result;
  uint32_t res;
  result.line_no = line_no;

  Label labels[MAX_CHARS];
  uint8_t numLabels = 0;
  int32_t offset;

  str[i] = strtok(instruction, delimit);
  while(str[i] != NULL) {
    i++;
    str[i] = strtok(NULL, delimit);
    if (str[i] != NULL){
	    if (strncmp(str[i], "#", 1) == 0){
		    str[i] += 1;
	    }
    }
  }

  // data_processing
  if (!strcmp(str[0], "mov")) {
    res = mov_a(get_val(str, 1), str[2]);
  } else if (!strcmp(str[0], "add")) {
    res = add_a(get_val(str, 2), get_val(str, 1), str[3]);
  } else if (!strcmp(str[0], "sub")) {
    res = sub_a(get_val(str, 2), get_val(str, 1), str[3]);
  } else if (!strcmp(str[0], "rsb")) {
    res = rsb_a(get_val(str, 2), get_val(str, 1), str[3]);
  } else if (!strcmp(str[0], "and")) {
    res = and_a(get_val(str, 2), get_val(str, 1), str[3]);
  } else if (!strcmp(str[0], "eor")) {
    res = eor_a(get_val(str, 2), get_val(str, 1), str[3]);
  } else if (!strcmp(str[0], "orr")) {
    res = orr_a(get_val(str, 2), get_val(str, 1), str[3]);
  } else if (!strcmp(str[0], "tst")) {
    res = tst_a(get_val(str, 1), str[2]);
  } else if (!strcmp(str[0], "teq")) {
    res = teq_a(get_val(str, 1), str[2]);
  } else if (!strcmp(str[0], "cmp")) {
    res = cmp_a(get_val(str, 1), str[2]);
  // multiply
  } else if (!strcmp(str[0], "mul")) {
    res = mul_a(get_val(str, 1), get_val(str, 2), get_val(str, 3));
  } else if (!strcmp(str[0], "mla")) {
    res = mla_a(get_val(str, 1), get_val(str, 2), get_val(str, 3), get_val(str, 4));
  // single data transfer -- wait
  } else if (!strcmp(str[0], "ldr")) {
    res = ldr_a(str);
  } else if (!strcmp(str[0], "str")) {
    res = str_a(str);
  // special
  } else if (!strcmp(str[0], "andeq")) {
    res = andeq_a();
  } else if (!strcmp(str[0], "lsl")) {
    res = lsl_a(get_val(str, 1), get_val(str, 2));
  // branch
  } else if (startsWith(str[0], "b")) {
    uint32_t addr = addr_finder(labels, str[1]);
    offset = (addr - line_no) & OFFSET_MASK;
    if (!strcmp(str[0], "beq")) { res = beq_a(offset); }
    else if (!strcmp(str[0], "bne")) { res = bne_a(offset); }
    else if (!strcmp(str[0], "bge")) { res = bge_a(offset); }
    else if (!strcmp(str[0], "blt")) { res = blt_a(offset); }
    else if (!strcmp(str[0], "bgt")) { res = bgt_a(offset); }
    else if (!strcmp(str[0], "ble")) { res = ble_a(offset); }
    else if (!strcmp(str[0], "bal") || !strcmp(str[0], "b")) { res = b_a(offset); }
    else { printf("Branch Error: Instruction not recognized"); }
  } else {
    Label lb;
    lb.name = str[0];
    lb.next_instr_addr = line_no;
    labels[numLabels] = lb;
    numLabels++;

    // do not increment when label found - syncs in main
    result.res = binary_int_to_chars(big_endian_to_little_endian(line_no));
    result.line_no -= 1;
  }
  result.res = binary_int_to_chars(little_endian_to_big_endian(res));

  return result;
}

int main(int argc, char *argv[]) {
  assert(argc == 3);

  char instruction[511];
  int cnt;
  FILE *fReadPtr;
  FILE *fWritePtr;
  ldr_buffer = malloc(sizeof(uint32_t) * 12);

// "test.s" is the name of the test file
  fReadPtr = fopen(argv[1], "r");
  fWritePtr = fopen(argv[2], "wb");

  if (fReadPtr == NULL) {
    printf("File Error: Unable to open file\n");
    exit(EXIT_FAILURE);
  }

  if (fWritePtr == NULL) {
    printf("File Error: Unable to write to file\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(instruction, sizeof(instruction), fReadPtr) != NULL) {
      Result curr = tokenize(instruction, cnt);
      char *res = curr.res;
      unsigned char buffer[4];
      uint32_t number = strtoll(res, NULL, 2);

      buffer[0] = (unsigned char) (number >> 24);
      buffer[1] = number >> 16;
      buffer[2] = number >> 8;
      buffer[3] = number;
     
      fwrite(buffer, sizeof(buffer) , 1, fWritePtr);
      uint8_t cntSyncer = curr.line_no;
      cnt = cntSyncer;
      cnt++;
      free(res);
  }
  free(ldr_buffer);

  if (feof(fReadPtr)) {
    fclose(fReadPtr);
    fclose(fWritePtr);
    exit(EXIT_SUCCESS);
  } else {
    fclose(fReadPtr);
    fclose(fWritePtr);
    printf("File Error: Unable to read file\n");
    exit(EXIT_FAILURE);
 }}
