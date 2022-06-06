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

    /* Check pre/post indexing */
    if (index_bit == 1){
        /* Pre-indexing */
    } else if (index_bit == 0){
        /* Post-indexing */
    }
}
