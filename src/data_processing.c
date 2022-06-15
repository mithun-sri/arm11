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
        reg.cpsr |= 1 << CPSR_C_OFFSET;
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

void and(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn & operand2;
    *rd = res;

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
    }
}

void eor(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn ^ operand2;
    *rd = res;

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
    }
}

void sub(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn - operand2;
    // uint8_t flag = (rn < operand2);
    *rd = res;

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
        // update_c(cpsr, flag);
    }
}

void rsb(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = operand2 - rn;
    // uint8_t flag = (operand2 < rn);
    *rd = res;

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
        // update_c(cpsr, flag);
    }
}

struct registers add(struct registers reg, uint8_t s_bit, uint8_t rn, uint32_t operand2, uint8_t rd) {
    uint32_t res = *reg.gen_regs[rn] + operand2;
    // for overflow either two numbers have MSB == 1 or one number has 1 and 
    // other has 0 and there is a previous carry producing a 0 as the MSB for the result
    uint8_t flag = ((extract_bits(rn, 31, 32) == 1) && (extract_bits(operand2, 31, 32) == 1)) || ((extract_bits(rn, 31, 32) == 0) && (extract_bits(operand2, 31, 32) == 1) && (extract_bits(res, 31, 32) == 0)) || ((extract_bits(rn, 31, 32) == 1) && (extract_bits(operand2, 31, 32) == 0) && (extract_bits(res, 31, 32) == 0));
    
    *reg.gen_regs[rd] = res;

    if (s_bit) {
        update_n(reg, res);
        update_z(reg, res);
        update_c(reg, flag);
    }
    return reg;
}

void tst(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2) {
    // uint32_t res = rn & operand2; 

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
    }
}

void teq(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2) {
    // uint32_t res = rn ^ operand2;

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
    }
}

void cmp(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2) {
    // uint32_t res = rn - operand2;
    // uint8_t flag = (rn < operand2);

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
        // update_c(cpsr, flag);
    }
}

void orr(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn | operand2;
    *rd = res;

    if (s_bit) {
        // update_n(cpsr, res);
        // update_z(cpsr, res);
    }
}

struct registers mov(struct registers reg, uint8_t s_bit, uint32_t operand2, uint8_t rd) {
    *reg.gen_regs[rd] = operand2;
    printf("Operand 2: %i", operand2);
    printf("%i\n", *reg.gen_regs[rd]);

    if (s_bit) {
        update_n(reg, operand2);
        update_z(reg, operand2);
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
		res.value = res.value | msb << (MOST_SIGNIFICANT_OFFSET - i);	
	}

	return res;
}

Operand2 rotate_right(uint8_t shift_amount, uint32_t content) {
	printf("Content: %i\n", content);
    Operand2 res = logical_right_shift(shift_amount, content);
	uint32_t mask = create_contiguous_mask(shift_amount);	
	res.value = res.value & (mask & content) << (MOST_SIGNIFICANT_OFFSET - shift_amount); 
	
	return res;
}

struct registers data_processing(uint32_t instruction, struct registers r) {
    uint8_t i_bit = (instruction >> I_BIT_OFFSET) & LAST_BIT_MASK;
    Opcode opcode = (int) extract_bits(instruction, 21, 25);
    uint8_t s_bit = (instruction >> S_BIT_OFFSET) & LAST_BIT_MASK;
    uint8_t rn_pos = extract_bits(instruction, 16, 20);
    uint32_t rn = *r.gen_regs[rn_pos];
    uint8_t rd_pos = extract_bits(instruction, 12, 16);
    uint8_t *rd = (uint8_t*) &r.gen_regs[rd_pos];
    uint32_t operand2 = extract_bits(instruction, 0, 12);
    printf("Operand 2: %i", operand2);
    uint32_t *cpsr = &r.cpsr;
    Operand2 operand2_with_carry;
  
    if (i_bit) {
        printf("I bit = 1\n");
        uint8_t rotate = 2 * (operand2 >> ROTATE_OFFSET);
        uint8_t content = operand2 & OPERAND_2_IMMEDIATE_MASK;
        operand2_with_carry = rotate_right(rotate, content);
	    operand2 = operand2_with_carry.value;
        printf("Operand 2 with carry: %i\n", operand2_with_carry.value);
    } else {
        printf("I Bit = 0\n");
        uint8_t rm_ptr = (uintptr_t) (operand2 & RM_MASK);
        // represents bit no. 4 in shift
        uint8_t optional_bit = (operand2 >> SHIFT_VALUE_OFFSET) & LAST_BIT_MASK;
        Shift shift_type = (operand2 >> SHIFT_TYPE_OFFSET) & LAST_TWO_BITS_MASK;
        uint8_t shift_amount;

        if (optional_bit) {
            // printf("Optional bit set\n");
            uint8_t shift_register = (uintptr_t) operand2 >> RS_OFFSET;
            shift_amount = (uintptr_t) &shift_register & (uint8_t) LAST_BYTE_MASK;
        } else {
            // printf("Optional bit not set\n");
            shift_amount = operand2 >> SHIFT_AMOUNT_OFFSET;
        }

        switch(shift_type) {
            case LSL: 
              operand2_with_carry = logical_left_shift(shift_amount, (uintptr_t) &rm_ptr); 
              operand2 = operand2_with_carry.value;
              // update_c(cpsr, operand2_with_carry.carry);
              break;
            case LSR: 
              operand2_with_carry = logical_right_shift(shift_amount, (uintptr_t) &rm_ptr); 
              // update_c(cpsr, operand2_with_carry.carry);
              break;
            case ASR: 
              operand2_with_carry = arithmetic_right_shift(shift_amount, (uintptr_t) &rm_ptr);
              operand2 = operand2_with_carry.value; 
              // update_c(cpsr, operand2_with_carry.carry);
              break;
            case ROR: 
              operand2_with_carry = rotate_right(shift_amount, (uintptr_t) &rm_ptr);
              operand2 = operand2_with_carry.value; 
              // update_c(cpsr, operand2_with_carry.carry);
              break;
            default: printf("shift_type error\n");
        }
    }

    if (succeeds(instruction, r)) {
        switch (opcode) {
        case AND: and(s_bit, cpsr, rn, operand2, rd); break;
        case EOR: eor(s_bit, cpsr, rn, operand2, rd); break;
        case SUB: sub(s_bit, cpsr, rn, operand2, rd); break;
        case RSB: rsb(s_bit, cpsr, rn, operand2, rd); break;
        case ADD: r = add(r, s_bit, rn_pos, operand2, rd_pos); break;
        case TST: tst(s_bit, cpsr, rn, operand2); break;
        case TEQ: teq(s_bit, cpsr, rn, operand2); break;
        case CMP: cmp(s_bit, cpsr, rn, operand2); break;
        case ORR: orr(s_bit, cpsr, rn, operand2, rd); break;
        case MOV: printf("mov\n"); r = mov(r, s_bit, operand2, rd_pos); break;
        default: printf("Invalid opcode: Operation not supported\n");
        }
    }
    return r;
}
