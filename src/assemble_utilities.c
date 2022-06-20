#include "assemble_utilities.h"

uint32_t big_endian_to_little_endian(uint32_t big_endian) {
    return ((big_endian >> THREE_BYTE_SHIFT) & BYTE_ZERO_MASK)  
        | ((big_endian >> ONE_BYTE_SHIFT) & BYTE_ONE_MASK)
        | ((big_endian << ONE_BYTE_SHIFT) & BYTE_TWO_MASK) 
        | ((big_endian << THREE_BYTE_SHIFT) & BYTE_THREE_MASK);
}

uint32_t little_endian_to_big_endian(uint32_t little_endian){
    return (((little_endian & 0x000000ff) << 24u)
        |  ((little_endian & 0x0000ff00) << 8u)
        |  ((little_endian & 0x00ff0000) >> 8u)  
        |  ((little_endian & 0xff000000) >> 24u));
}

char *binary_int_to_chars(uint32_t little_endian) {
    uint32_t num = little_endian;
    char *binary_number = malloc(sizeof(char) * NUMBER_OF_INSTRUCTION_BITS);

    for (int i=1; i<=NUMBER_OF_INSTRUCTION_BITS; i++) {
        if (num % 2) {
            binary_number[NUMBER_OF_INSTRUCTION_BITS-i] = ONE;
        } else {
            binary_number[NUMBER_OF_INSTRUCTION_BITS-i] = ZERO;
        }
        num = num / 2;
    }
    return binary_number;
}

uint32_t* ldr_buffer;
