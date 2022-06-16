#include "single_data_transfer.h"

uint32_t perform_shift(uint32_t val, uint8_t shift_amount, int shift_type){
	Operand2 offset;
	switch(shift_type){
		case 0:
			/* Logical left */
			offset = logical_left_shift(shift_amount, val);
			return offset.value;
		case 1: 
			/* Logical right */
			offset = logical_right_shift(shift_amount, val);
			return offset.value;
		case 2: 
			/* Arithmetic right */
			offset = arithmetic_right_shift(shift_amount, val);
			return offset.value;
		case 3:
			/* Rotate right */
			offset = rotate_right(shift_amount, val);
			return offset.value;
		default:
			printf("Error! Unknown shift type!");
			return 0;
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
struct registers register_write(struct registers reg, uint8_t dest, uint32_t value){
    // printf("Writing\n");
	*reg.gen_regs[dest] = value;
	return reg;
}

/* Write from register to memory */
void memory_write(uint8_t *location, uint32_t value){
    uint8_t *ptr = location;
    for (int i = 0; i < BYTES_PER_WORD; i++){
	*ptr = (uint8_t) extract_bits(value, i * 8, (i+1) * 8);
        ptr++;
    }
}

static uint32_t read_memory(uint8_t* address){
  uint32_t result = 0;
  uint8_t *ptr = address;
  for (uint8_t j = 0; j < BYTES_PER_WORD; j++) {
    result |= ((*ptr) << (j * 8));
    ptr++; 
  }
  return result;
}

static void display_memory(uint32_t address){
	uint32_t result = read_memory(&memory[address]);
	for (uint32_t j = 0; j < BYTES_PER_WORD; j++) {
		uint8_t endian_value = (uint8_t) extract_bits(result, j * 8, (j + 1) * 8);
		printf("%02x", endian_value); 
	}
	printf("\n");
}

struct registers perform_transfer(struct registers reg, int l_bit, uint32_t new_address, uint8_t rd, uint8_t* memory){
    if (l_bit == 1){
        /* Load instruction */
		// printf("Writing see");	
		// display_memory(new_address);
		if (new_address < MEMORY_CAPACITY - BYTES_PER_WORD){
			uint8_t *ptr = &memory[new_address];
    		uint32_t value = 0;
    		for (uint8_t i = 0; i < BYTES_PER_WORD; i++) {
        		value |= *ptr << (i * 8);
				ptr++;
    		}
		reg = register_write(reg, rd, value);
		}
		else {
			printf("Error: Out of bounds memory access at address 0x");
			display_memory(new_address);
		}
	} else{
        /* Store instruction */
        memory_write((uint8_t*)&memory[new_address], *reg.gen_regs[rd]);
    }
	return reg;
}

struct registers single_data_transfer(uint32_t instruction, struct registers r, uint8_t* memory){
	if (succeeds(instruction, r)){
		int l_bit = extract_bits(instruction, 20, 21);
		int p_bit = extract_bits(instruction, 24, 25);
		int up_bit = extract_bits(instruction, 23, 24);
		uint8_t rn_location = extract_bits(instruction, 16, 20);
		uint32_t rn = *r.gen_regs[rn_location];
		uint8_t rd_location = extract_bits(instruction, 12, 16);
		uint32_t offset = find_offset(instruction, r);

		/* Check pre/post indexing */
		if (p_bit == 1){
			/* Pre-indexing */
			uint32_t new_address = compute_address(rn, offset, up_bit);
			r = perform_transfer(r, l_bit , new_address, rd_location, memory);
		} else {
			/* Post-indexing */
			r = perform_transfer(r, l_bit, rn, rd_location, memory);
			uint32_t new_address = compute_address(rn, offset, up_bit);
			/* Update base register */
			r = register_write(r, rn_location, new_address);
		}
	}
	return r;
}
