#include <stdio.h>
#include <stdint.h>
#include "data_processing.h"

struct registers update_n(struct registers reg, uint32_t res) {
    if ((res & MOST_SIGNIFICANT) != 0) {
        reg.cpsr |= 1 << CPSR_N_OFFSET;
    } else {
        reg.cpsr &= MOST_SIGNIFICANT;
    }
    return reg;
}

struct registers update_z(struct registers reg, uint32_t res) {
    if (res == 0) {
        reg.cpsr |= 1 << CPSR_Z_OFFSET;
    } else {
        reg.cpsr &= Z_CLEAR;
    }
    return reg;
}

struct registers update_c(struct registers reg, uint8_t flag) {
    if (flag == 1) {
        reg.cpsr &= 1 << CPSR_C_OFFSET;
    } else {
        reg.cpsr &= C_CLEAR;
    }
    return reg;
}

struct registers update_v(struct registers reg, uint8_t flag) {
    if (flag == 1) {
        reg.cpsr |= 1 << CPSR_V_OFFSET;
    } else {
        reg.cpsr &= V_CLEAR;
    }
    return reg;
}

struct registers and(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd) {
    uint32_t res = *reg.gen_regs[rn] & operand2;
    *reg.gen_regs[rd] = res;

    if (s_bit){
        reg = update_n(reg, res);
        reg = update_z(reg, res);
    }
	return reg;
}
struct registers eor(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd){
    uint32_t res = *reg.gen_regs[rn] ^ operand2;
    *reg.gen_regs[rd] = res;

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
    }
    return reg;
}

struct registers sub(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd) {
    uint32_t res = *reg.gen_regs[rn] - operand2;
    uint8_t flag = (*reg.gen_regs[rn] < operand2);
    *reg.gen_regs[rd] = res;

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
        reg = update_c(reg, flag);
    }
    return reg;
}

struct registers rsb(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd) {
    uint32_t res = operand2 - *reg.gen_regs[rn];
    uint8_t flag = (operand2 < *reg.gen_regs[rn]);
    *reg.gen_regs[rd] = res;

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
        reg = update_c(reg, flag);
    }
    return reg;
}

struct registers add(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd) {
    // printf("ADD");
    uint32_t res = *reg.gen_regs[rn] + operand2;
    // for overflow either two numbers have MSB == 1 or one number has 1 and 
    // other has 0 and there is a previous carry producing a 0 as the MSB for the result
    uint8_t flag = ((extract_bits(rn, 31, 32) == 1) && (extract_bits(operand2, 31, 32) == 1)) || ((extract_bits(rn, 31, 32) == 0) && (extract_bits(operand2, 31, 32) == 1) && (extract_bits(res, 31, 32) == 0)) || ((extract_bits(rn, 31, 32) == 1) && (extract_bits(operand2, 31, 32) == 0) && (extract_bits(res, 31, 32) == 0));
    
    *reg.gen_regs[rd] = res;

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
        reg = update_c(reg, flag);
    }
    return reg;
}

struct registers tst(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2) {
    uint32_t res = *reg.gen_regs[rn] & operand2; 

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
    }
    return reg;
}

struct registers teq(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2) {
    int32_t res = *reg.gen_regs[rn] ^ operand2;

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
    }
    return reg;
}

struct registers cmp(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2) {
    uint32_t res = *reg.gen_regs[rn] - operand2;
    uint8_t flag = (*reg.gen_regs[rn] < operand2);

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
        reg = update_c(reg, flag);
    }
    return reg;
}

struct registers orr(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd) {
    uint32_t res = *reg.gen_regs[rn] | operand2;
    *reg.gen_regs[rd] = res;

    if (s_bit) {
        reg = update_n(reg, res);
        reg = update_z(reg, res);
    }
    return reg;
}

struct registers mov(struct registers reg, uint8_t s_bit, uint32_t operand2, uint8_t rd) {
    *reg.gen_regs[rd] = operand2;
    // printf("Operand 2: %i", operand2);

    if (s_bit) {
        reg = update_n(reg, operand2);
        reg = update_z(reg, operand2);
    }
    return reg;
}

Operand2 logical_left_shift(uint8_t shift_amount, uint32_t content) {
	Operand2 res;
	res.value = (uint32_t) (content << shift_amount);
	res.carry = get_bit(1 << (REGISTER_BITS - shift_amount) & content); 

	return res; 
}

Operand2 logical_right_shift(uint8_t shift_amount, uint32_t content) {
	Operand2 res;
	res.value = (uint32_t) (content >> shift_amount);
	res.carry = get_bit(1 << shift_amount & content); 

	return res; 
}
	
Operand2 arithmetic_right_shift(uint8_t shift_amount, uint32_t content) {
	Operand2 res = logical_right_shift(shift_amount, content);
	uint8_t msb = get_bit(MOST_SIGNIFICANT & content);
	for (int i=0; i<shift_amount; i++) {
		res.value = res.value | msb << (REGISTER_BITS - i);	
	}

	return res;
}

Operand2 rotate_right(uint8_t shift_amount, uint32_t content) {
    // Operand2 res;
    // res.value = extract_bits(content, shift_amount, 32);
    // res.carry = 0;

    // if (shift_amount > 0 ){
    //     res.value |= extract_bits(content, 0, shift_amount) << (32 - shift_amount);
    //     res.carry = extract_bits(content, shift_amount - 1, shift_amount);

    // }

    Operand2 res = logical_right_shift(shift_amount, content);
	uint32_t mask = create_contiguous_mask(shift_amount);	
	res.value = res.value | ((mask & content) << (REGISTER_BITS - shift_amount)); 
	
	return res;
}

struct registers data_processing(uint32_t instruction, struct registers r) {
    uint8_t i_bit = (instruction >> I_BIT_OFFSET) & LAST_BIT_MASK;
    Opcode opcode = (int) extract_bits(instruction, 21, 25);
    // printf("%i\n", opcode);
    uint8_t s_bit = (instruction >> S_BIT_OFFSET) & LAST_BIT_MASK;
    uint8_t rn_pos = extract_bits(instruction, 16, 20);
    // uint32_t rn = *r.gen_regs[rn_pos];
    uint8_t rd_pos = extract_bits(instruction, 12, 16);
    // uint8_t *rd = (uint8_t*) &r.gen_regs[rd_pos];
    uint32_t operand2 = extract_bits(instruction, 0, 12);
    // printf("Operand 2 (data_processing): %i\n", operand2);
    // uint32_t *cpsr = &r.cpsr;
    Operand2 operand2_with_carry;
    // printf("CPSR: %i\n", r.cpsr);
  
    if (i_bit) {
        uint8_t rotate = 2 * (operand2 >> ROTATE_OFFSET);
        uint8_t content = operand2 & OPERAND_2_IMMEDIATE_MASK;
        operand2_with_carry = rotate_right(rotate, content);
	    operand2 = operand2_with_carry.value;
       //  printf("Operand 2 with carry (i_bit = 1): %i\n", operand2_with_carry.value);
    } else {
       // printf("I Bit = 0\n");
        uint8_t rm_ptr = extract_bits(instruction, 0, 4);
        uint8_t optional_bit = (operand2 >> SHIFT_VALUE_OFFSET) & LAST_BIT_MASK;
        Shift shift_type = extract_bits(instruction, 5, 7);
        uint8_t shift_amount;

        if (optional_bit) {
            // printf("Optional bit set\n");
            uint8_t shift_register = (uintptr_t) operand2 >> RS_OFFSET;
            shift_amount = (uintptr_t) &shift_register & (uint8_t) LAST_BYTE_MASK;
        } else {
            // printf("Optional bit not set\n");
            shift_amount = operand2 >> SHIFT_AMOUNT_OFFSET;
        }

        // printf("Shift type: %i", shift_type);
        switch(shift_type) {
            case LSL:
                // printf("LSL\n");
                operand2_with_carry = logical_left_shift(shift_amount, *r.gen_regs[rm_ptr]); 
                operand2 = operand2_with_carry.value;
                r = update_c(r, operand2_with_carry.carry);
                break;
            case LSR: 
             //   printf("LSR\n");
                operand2_with_carry = logical_right_shift(shift_amount, *r.gen_regs[rm_ptr]); 
                r = update_c(r, operand2_with_carry.carry);
                break;
            case ASR: 
               // printf("ASR");
                operand2_with_carry = arithmetic_right_shift(shift_amount, *r.gen_regs[rm_ptr]);
                operand2 = operand2_with_carry.value; 
                r = update_c(r, operand2_with_carry.carry);
                break;
            case ROR: 
                //printf("ROR");
                operand2_with_carry = rotate_right(shift_amount, *r.gen_regs[rm_ptr]);
                operand2 = operand2_with_carry.value; 
                r = update_c(r, operand2_with_carry.carry);
                break;
            default: printf("shift_type error\n");
        }
    }
    // printf("OPCODE: %i", opcode);
    // printf("CONDITION CODE: %i\n", r.cpsr);

    if (succeeds(instruction, r)) {
        // printf("PASSES\n");
        switch (opcode) {
        case AND: r = and(r, s_bit, rn_pos, operand2, rd_pos); break;
        case EOR: r = eor(r, s_bit, rn_pos, operand2, rd_pos); break;
        case SUB: r = sub(r, s_bit, rn_pos, operand2, rd_pos); break;
        case RSB: r = rsb(r, s_bit, rn_pos, operand2, rd_pos); break;
        case ADD: //printf("add\n"); 
                    r = add(r, s_bit, rn_pos, operand2, rd_pos); break;
        case TST: r = tst(r, s_bit, rn_pos, operand2); break;
        case TEQ: r = teq(r, s_bit, rn_pos, operand2); break;
        case CMP: r = cmp(r, s_bit, rn_pos, operand2); break;
        case ORR: r = orr(r, s_bit, rn_pos, operand2, rd_pos); break;
        case MOV: // printf("mov\n"); 
                r = mov(r, s_bit, operand2, rd_pos); break;
        default: printf("Invalid opcode: Operation not supported\n");
        }
    }
    return r;
}
