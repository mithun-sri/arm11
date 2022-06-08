#include <stdlib.h>
#include <stdio.h>
#include "emulate.h"

int single_data_transfer(int l_bit, int offset_bit, int index_bit, int up_bit, uint32_t rn, uint32_t offset, uint32_t rd){
    /* Check pre/post indexing */
    if (index_bit == 1){
        /* Pre-indexing */
        uint32_t new_address = compute_address(rn, offset, up_bit);
        perform_transfer(l_bit , new_address, rd);
    } else if (index_bit == 0){
        /* Post-indexing */
        perform_transfer(l_bit, rn, rd);
        uint32_t new_address = compute_address(rn, offset, up_bit);
        /* Update base register */
        register_write(rn, new_address);
    }
    return EXIT_SUCCESS;
}

void perform_transfer(int l_bit, uint32_t new_address, uint32_t rd){
    if (l_bit == 1){
        /* Load instruction */
        register_write(&rd, new_address);
    } else if (l_bit == 0){
        /* Store instruction */
        memory_write(&rd, new_address);
    }
}

/* Write from memory to register */
void register_write(uint32_t *dest, uint32_t value){
    *dest = value;
}

/* Write from register to memory */
void memory_write(uint8_t *location, uint32_t value){
    uint8_t *ptr = location;
    for (int i = 0; i < BYTES_PER_WORD; i++){
        uint32_t MASK = 2^((i + 1) * 8) - 1;
        *ptr = (value & MASK) >> (i * 8);
        ptr++;
    }
}

uint32_t compute_address(uint32_t value, uint32_t offset, int up_bit){
    uint32_t address = 0;
    if (up_bit == 1){
        address = value + offset;
    } else if (up_bit == 0){
        address = value - offset;
    }
    return address;
}