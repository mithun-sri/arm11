#include <stdlib.h>
#include <stdio.h>

int single_data_transfer(int l_bit, int offset_bit, int index_bit, int up_bit, int rn, uint16_t *offset, uint32_t *rd){
    /* Check CPSR Condition */

    /* Calculate offset */
    if (offset_bit == 1){
        /* Shifted register */
    } else if (offset_bit == 0){
        /* Immediate value */
    }

    uint32_t new_address;

    if (up_bit == 1){
        new_address = rn + *offset;
    } else if (up_bit == 0){
        new_address = rn - *offset;
    }

    /* Check pre/post indexing */
    if (index_bit == 1){
        /* Pre-indexing */
        transfer(l_bit);
    } else if (index_bit == 0){
        /* Post-indexing */
        transfer(l_bit);
    }
}

void transfer(int l_bit){
    if (l_bit == 1){
        /* Load instruction */
        register_write();
    } else if (l_bit == 0){
        /* Store instruction */
        memory_write();
        register_write();
    }
}

void register_write(){

}

void memory_write(){

}
