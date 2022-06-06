#include <stdio.h>
#include <stdint.h>
#include "reg.c"

#define BIT_27_MASK 0x8000000
#define BIT_27_OFFSET 27
#define BIT_26_MASK 0x4000000
#define BIT_26_OFFSET 26
#define I_BIT_MASK 0x2000000
#define I_BIT_OFFSET 25
#define OPCODE_MASK 0x1e00000
#define OPCODE_OFFSET 21
#define S_BIT_MASK 0x100000
#define S_BIT_OFFSET 20
#define RN_MASK 0xf0000
#define RN_OFFSET 16
#define RD_MASK 0xf000
#define RD_OFFSET 12
#define OPERAND_2_MASK 0xfff
#define OPERAND_2_IMMEDIATE_MASK 0xff
#define ROTATE_OFFSET 8
#define RM_MASK 0xf
#define SHIFT_VALUE_MASK 0xff0
#define SHIFT_OPTIONAL_BIT_MASK 0x10
#define SHIFT_VALUE_OFFSET 4
#define SHIFT_TYPE_MASK 0x6
#define LAST_BIT_OFFSET 1
#define SHIFT_AMOUNT_OFFSET 7
#define LAST_BIT_MASK 0x1
#define CPSR_N_OFFSET 31
#define CPSR_Z_OFFSET 30
#define CPSR_C_OFFSET 29
#define CPSR_V_OFFSET 28
#define Z_CLEAR 0xbfffffff
#define C_CLEAR 0xdfffffff
#define V_CLEAR 0xefffffff
#define MOST_SIGNIFICANT 0x80000000
