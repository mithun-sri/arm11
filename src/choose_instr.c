#include <stdio.h>
#include <stdlib.h>

void choose_instruction (uint32_t instr){
  uint8_t bit_27 = (instruction >> 27) & 1;
  uint8_t bit_26 = (instruction >> 26) & 1;
  uint8_t bit_22_27 = (instruction >> 22) & ((1 << 5));
  uint8_t bit_4_7 = (instruction >> 4) & ((1 << 3));
  
  if (bit_27 == 1) {
    branch(instruction);
  }
  
  if (bit_26 == 1) {
    single_data_transfer(instruction);
  } else {
    if (bit_22_27 == 0 && bit_4_7 == 9) {
      multiply(instruction);
      } else {
        data_processing(instruction);
      }
   }
}    
 



