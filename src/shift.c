#include <stdlib.h>
#include <stdio.h>

int transform_operand(uint32_t instr){
	/* Obtain immediate bit */
	int immediate_bit;
	uint32_t *rd;

	if (immediate_bit == 1){
		/* Operand2 is an immediate value */
		uint32_t imm_value = zero_extend(immedate_bits);
		uint32_t num_rotations = 2 * rotate_bits;
		uint32_t rotated_imm = rotate_right(imm_value, num_rotations);
		*rd = rotated_imm;
	} else if (immediate_bit == 0){
		/* Operand2 is a register */

		/* Extract the 4th bit in instruction*/
		int bit_4;
		/* Extract the shift type in the instruction */
		int shift_type;
		if (bit_4 == 0){
			/* Shift by a constant amount */
			uint32_t val;
		} else {
			/* Shift by register value */
			uint32_t val;
		}
		
		uint32_t shifted_val = shift(val, shift_type);
		*rd = shifted_val;
		}
	} else {
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

uint32_t shift(uint32_t val, int shift_type){
	switch(shift_type):
	case 0:
		logical_left();
		break;
	case 1:
		logical_right();
		break;
	case 2:
		arithmetic_right();
		break;
	case 3:
		rotate_right();
		break;
	default:
		printf("Error! Unsupported instruction!");
}
