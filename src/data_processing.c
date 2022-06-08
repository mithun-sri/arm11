#include <stdio.h>
#include <stdint.h>
#include "data_processing.h"

void update_n(uint32_t* cpsr, uint32_t res) {
    if ((res & MOST_SIGNIFICANT) != 0) {
        *cpsr |= 1 << CPSR_N_OFFSET;
    } else {
        *cpsr &= MOST_SIGNIFICANT;
    }
}

void update_z(uint32_t* cpsr, uint32_t res) {
    if (res == 0) {
        *cpsr |= 1 << CPSR_Z_OFFSET;
    } else {
        *cpsr &= Z_CLEAR;
    }
}

void update_c(uint32_t* cpsr, uint8_t flag) {
    if (flag == 1) {
        *cpsr |= 1 << CPSR_C_OFFSET;
    } else {
        *cpsr &= C_CLEAR;
    }
}

void update_v(uint32_t* cpsr, uint8_t flag) {
    if (flag == 1) {
        *cpsr |= 1 << CPSR_V_OFFSET;
    } else {
        *cpsr &= V_CLEAR;
    }
}

void and(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn & operand2;
    *rd = res;

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
    }
}

void eor(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn ^ operand2;
    *rd = res;

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
    }
}

void sub(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn - operand2;
    uint8_t flag = (rn < operand2);
    *rd = res;

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
        update_c(cpsr, flag);
    }
}

void rsb(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = operand2 - rn;
    uint8_t flag = (operand2 < rn);
    *rd = res;

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
        update_c(cpsr, flag);
    }
}

void add(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn + operand2;
    // for overflow either two numbers have MSB == 1 or one number has 1 and 
    // other has 0 and there is a previous carry producing a 0 as the MSB for the result
    uint8_t flag = (extract_bits(rn, 31, 32) == 1) && (extract_bits(operand2, 31, 32) == 1) 
    || (extract_bits(rn, 31, 32) == 0) && extract_bits(operand2, 31, 32) == 1 && (extract_bits(res, 31, 32) == 0)
    || (extract_bits(rn, 31, 32) == 1) && extract_bits(operand2, 31, 32) == 0 && (extract_bits(res, 31, 32) == 0);
    
    *rd = res;

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
        update_c(cpsr, flag);
    }
}

void tst(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2) {
    uint32_t res = rn & operand2; 

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
    }
}

void teq(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2) {
    uint32_t res = rn ^ operand2;

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
    }
}

void cmp(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2) {
    uint32_t res = rn - operand2;
    uint8_t flag = (rn < operand2);

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
        update_c(cpsr, flag);
    }
}

void orr(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    uint32_t res = rn | operand2;
    *rd = res;

    if (s_bit) {
        update_n(cpsr, res);
        update_z(cpsr, res);
    }
}

void mov(uint8_t s_bit, uint32_t* cpsr, uint32_t rn, uint32_t operand2, uint8_t* rd) {
    *rd = operand2;

    if (s_bit) {
        update_n(cpsr, operand2);
        update_z(cpsr, operand2);
    }
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
	Operand2 res = logical_right_shift(shift_amount, content);
	uint32_t mask = create_contigouous_mask(shift_amount);	
	res.value = res.value & (mask & content) << (MOST_SIGNIFICANT_OFFSET - shift_amount); 
	
	return res;
}

void manage(uint32_t instruction, struct registers* r) {
    uint8_t bit27 = (instruction >> BIT_27_OFFSET) & LAST_BIT_MASK;
    uint8_t bit26 = (instruction >> BIT_26_OFFSET) & LAST_BIT_MASK;
    uint8_t i_bit = (instruction >> I_BIT_OFFSET) & LAST_BIT_MASK;
    Opcode opcode = (instruction >> OPCODE_OFFSET) & LAST_FOUR_BITS_MASK;
    uint8_t s_bit = (instruction >> S_BIT_OFFSET) & LAST_BIT_MASK;
    uint8_t rn_pos = (instruction >> RN_OFFSET) & LAST_FOUR_BITS_MASK;
    uint32_t rn = r->general[rn_pos];
    uint8_t rd_pos = (instruction >> RD_OFFSET) & LAST_FOUR_BITS_MASK;
    uint8_t *rd = &r->general[rd_pos];
    uint32_t operand2 = (instruction & OPERAND_2_MASK);
    uint32_t *cpsr = &r->cpsr;
  
    if (i_bit) {
        uint8_t rotate = 2 * (operand2 >> ROTATE_OFFSET);
        uint8_t content = operand2 & OPERAND_2_IMMEDIATE_MASK;
        operand2 = rotate_right(rotate, content);
    } else {
        uint8_t* rmPtr = operand2 & RM_MASK;
        // represents bit no. 4 in shift
        uint8_t optional_bit = (operand2 >> SHIFT_VALUE_OFFSET) & LAST_BIT_MASK;
        Shift shift_type = (operand2 >> SHIFT_TYPE_OFFSET) & LAST_TWO_BITS_MASK;
        uint8_t shift_amount;
        Operand2 new_operand2_with_carry = logical_left_shift(shift_amount, &rmPtr);

        if (optional_bit) {
            uint8_t *shift_register = operand2 >> RS_OFFSET;
            shift_amount = &shift_register & LAST_BYTE_MASK;
        } else {
            shift_amount = operand2 >> SHIFT_AMOUNT_OFFSET;
        }

        switch(shift_type) {
            case LSL: 
              operand2 = new_operand2_with_carry.value; update_c(cpsr, new_operand2_with_carry.carry); break;
              update_c(cpsr, new_operand2_with_carry.carry);
            case LSR: 
              operand2 = logical_right_shift(shift_amount, &rmPtr).value; 
              update_c(cpsr, new_operand2_with_carry.carry);
              break;
            case ASR: 
              operand2 = arithmetic_right_shift(shift_amount, &rmPtr).value; 
              update_c(cpsr, new_operand2_with_carry.carry);
              break;
            case ROR: 
              operand2 = rotate_right(shift_amount, &rmPtr).value; 
              update_c(cpsr, new_operand2_with_carry.carry);
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
        case ADD: add(s_bit, cpsr, rn, operand2, rd); break;
        case TST: tst(s_bit, cpsr, rn, operand2); break;
        case TEQ: teq(s_bit, cpsr, rn, operand2); break;
        case CMP: cmp(s_bit, cpsr, rn, operand2); break;
        case ORR: orr(s_bit, cpsr, rn, operand2, rd); break;
        case MOV: mov(s_bit, cpsr, rn, operand2, rd); break;
        default: printf("Invalid opcode: Operation not supported\n");
        }
    }
}
