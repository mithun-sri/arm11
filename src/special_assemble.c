#include "special_assemble.h"

uint32_t lsl_a(uint8_t rn, uint8_t op2) {
     return (COND << COND_OFFSET) + (MOV_OPCODE << OPCODE_OFFSET) 
    + (rn << RD_OFFSET) + (op2 << INTEGER_SHIFT) + rn;
}

uint32_t andeq_a() {
    return HALT;
}