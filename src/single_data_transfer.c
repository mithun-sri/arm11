#include "single_data_transfer.h"

uint32_t perform_shift(uint32_t val, uint8_t shift_amount, int shift_type){
	Operand2 offset;
	switch(shift_type){
		case 0:
			/* Logical left */
			offset = logical_left_shift(shift_amount, val);
			return offset.value;
			break;
		case 1: 
			/* Logical right */
			offset = logical_right_shift(shift_amount, val);
			return offset.value;
			break;
		case 2: 
			/* Arithmetic right */
			offset = arithmetic_right_shift(shift_amount, val);
			return offset.value;
			break;
		case 3:
			/* Rotate right */
			offset = rotate_right(shift_amount, val);
			return offset.value;
			break;
		default:
			printf("Error! Unknown shift type!");
			break;
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

uint32_t find_offset(uint32_t instr, struct registers r){
	int i_bit = extract_bits(instr, 25, 26);
	if (i_bit == 1){
		/* Shifted register */
		int rm_loc = extract_bits(instr, 0, 4);
		uint32_t rm = *r.gen_regs[rm_loc];
		int shift_type = extract_bits(instr, 5, 7);
		int specify_bit = extract_bits(instr, 4, 5);
		if (specify_bit){
			/* Shift specified by a register */
			int shift_register = extract_bits(instr, 8, 12);
			uint8_t shift_amount = (uint8_t) *r.gen_regs[shift_register];
			return perform_shift(rm, shift_amount, shift_type);
		} else {
			/* Shift specified by a constant amount */
			uint8_t shift_amount = (uint16_t) extract_bits(instr, 7, 12);
			return perform_shift(rm, shift_amount, shift_type);
		}
	} else {
		/* Unsigned 12 bit immediate offset */
		return (uint16_t) extract_bits(instr, 0, 12);
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

void perform_transfer(int l_bit, uint32_t new_address, uint32_t rd){
    if (l_bit == 1){
        /* Load instruction */
        register_write(&rd, new_address);
    } else if (l_bit == 0){
        /* Store instruction */
        memory_write((uint8_t*)&rd, new_address);
    }
}

void single_data_transfer(uint32_t instruction, struct registers r){
	if (succeeds(instruction, r) != 1){
		exit(EXIT_FAILURE);
	}
	int l_bit = extract_bits(instruction, 20, 21);
	int p_bit = extract_bits(instruction, 24, 25);
	int up_bit = extract_bits(instruction, 23, 24);
	int rn_location = extract_bits(instruction, 16, 20);
	uint32_t *rn = (uint32_t*) &r.gen_regs[rn_location];
	int rd_location = extract_bits(instruction, 12, 16);
	uint32_t rd = *r.gen_regs[rd_location];
	uint32_t offset = find_offset(instruction, r);

    /* Check pre/post indexing */
    if (p_bit == 1){
        /* Pre-indexing */
        uint32_t new_address = compute_address(*rn, offset, up_bit);
        perform_transfer(l_bit , new_address, rd);
    } else {
        /* Post-indexing */
        perform_transfer(l_bit, *rn, rd);
        uint32_t new_address = compute_address(*rn, offset, up_bit);
        /* Update base register */
        register_write((uint32_t*) &rn, new_address);
    }
}
