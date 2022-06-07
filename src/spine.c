#include <stdio.h>
#include <stdlib.h>

#include "reg.c" 

#define END_INDICATOR 0     // End of instructions when instruction is 000..00
#define INSTR_SIZE_BYTES 4  // Each instruction is 4 bytes long


while (r.ir != END_INDICATOR) {
  // decode the instruction in the instruction register
  // based on the decoding, execute the instruction
  r.pc += 4;
  r.ir = *(array_start + r.pc);
 }
  


  
