#include "assemble_utilities.h"

uint32_t big_endian_to_little_endian(uint32_t big_endian) {
    return ((big_endian >> ONE_BYTE_SHIFT) & BYTE_ZERO_MASK)  
        | ((big_endian >> ONE_BYTE_SHIFT) & BYTE_ONE_MASK)
        | ((big_endian << ONE_BYTE_SHIFT) & BYTE_TWO_MASK) 
        | ((big_endian<<THREE_BYTE_SHIFT) & BYTE_THREE_MASK);
}

