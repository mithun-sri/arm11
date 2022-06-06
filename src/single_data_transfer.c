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
    
    uint32_t base_register;
    /* Check pre/post indexing */
    if (index_bit == 1){
        /* Pre-indexing */
        uint32_t new_address = compute_address(base_register, *offset, up_bit);
        transfer(l_bit , new_address);
    } else if (index_bit == 0){
        /* Post-indexing */
        transfer(l_bit, rn);
        base_register = compute_address(base_register, *offset, up_bit);
        /* Update base register */
        register_write(base_register);
    }
}

void transfer(int l_bit, uint32_t new_address){
    if (l_bit == 1){
        /* Load instruction */
        /* Write to register */
    } else if (l_bit == 0){
        /* Store instruction */
        /* Write to memory */
    }
}

void register_write(uint32_t address){

}

void memory_write(uint32_t address){

}

uint32_t compute_address(uint32_t *rn, uint32_t *offset, int up_bit){
    uint32_t new_address = 0;
    if (up_bit == 1){
        new_address = rn + *offset;
    } else if (up_bit == 0){
        new_address = rn - *offset;
    }
}