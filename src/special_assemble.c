#include "special_assemble.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t lsl_a(char** str) {
   uint32_t int_amt;
     if ((strncmp(str[2], "0x", 2)) == 0){
        // Hex
        int_amt = strtol(str[2] + 2, NULL, 16);
     } else {
        // Base 10
        int_amt = atoi(str[2]);
     }
     uint32_t rm = atoi(str[1] + 1);
     return (COND << COND_OFFSET) + (MOV_OPCODE << OPCODE_OFFSET) 
    + (rm << RD_OFFSET) + (int_amt << INTEGER_SHIFT) + rm;
}

uint32_t andeq_a() {
    return HALT;
}