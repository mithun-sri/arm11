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

uint32_t find_memory_address(uint32_t base_value, uint32_t offset, uint32_t instr){
	uint32_t up_bit = extract_bits(instr, 23, 24);
	if (up_bit){
		return base_value + offset;
	} else {
		return base_value - offset;
	}
}

uint32_t find_offset(uint32_t instr, struct registers r){
	int i_bit = extract_bits(instr, 25, 26);
	if (i_bit) {
		int rm_loc = extract_bits(instr, 0, 4);
		uint32_t rm = *r.gen_regs[rm_loc];
		int shift_type = extract_bits(instr, 5, 7);
		uint8_t shift_amount = extract_bits(instr, 7, 12);
		return perform_shift(rm, shift_amount, shift_type);
	} else {
		return extract_bits(instr, 0, 12);
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

static uint32_t read_memory(uint8_t* ptr){
	uint32_t value = 0;
	for (uint8_t i = 0; i < BYTES_PER_WORD; i++) {
		value |= *ptr << (i * 8);
		ptr++;
	}
	return value;
}

static uint8_t memory_in_bounds(uint32_t addr){
	if (addr > MEMORY_CAPACITY - BYTES_PER_WORD){
		return 1;
	}
	return 0;
}

static struct registers perform_transfer(struct registers r, uint32_t addr, uint32_t l_bit, uint32_t rd_loc) {
    uint32_t word;
    if (l_bit) {
        if (memory_in_bounds(addr) == 0) {
            word = read_memory(&memory[addr]);
            r = register_write(r, rd_loc, word);
        }
	else {
		printf("Error: Out of bounds memory access at address 0x%08x\n", addr);
	}
    } else {
        if ((rd_loc >= 12) == 0) {
            word = *r.gen_regs[rd_loc];
            memory_write(&memory[addr], word);
        }
    }
	return r;
}


struct registers single_data_transfer(uint32_t instruction, struct registers r, uint8_t* memory){
	if (succeeds(instruction, r)){
		int l_bit = extract_bits(instruction, 20, 21);
		int p_bit = extract_bits(instruction, 24, 25);
		uint8_t rn_location = extract_bits(instruction, 16, 20);
		//printf("Base register : $%i. Value : %08x\n", rn_location ,*r.gen_regs[rn_location]);
		uint8_t rd_location = extract_bits(instruction, 12, 16);
		int32_t offset = find_offset(instruction, r);

		if (p_bit){
			int32_t addr;
			if (rn_location == 15){
				addr = find_memory_address(*r.gen_regs[rn_location], offset, instruction);
			} else {
				addr = find_memory_address(*r.gen_regs[rn_location], offset, instruction);
			}
		//	printf("Memory addr: 0x%08x\n", addr);
			r = perform_transfer(r, addr, l_bit, rd_location);
		} else {
			r = perform_transfer(r, *r.gen_regs[rn_location], l_bit, rd_location);
			uint32_t addr = find_memory_address(*r.gen_regs[rn_location], offset, instruction);
			r = register_write(r, rn_location, addr);
		}
	}
	return r;
}
