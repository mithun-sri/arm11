#ifndef SINGLE_DATA_TRANSFER_ASSEMBLE_H
#define SINGLE_DATA_TRANSFER_ASSEMBLE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "data_processing_assemble.h"
#include "assemble_utilities.h"
#define UP_BIT_INDEX 23
#define L_BIT_INDEX 20
#define P_BIT_INDEX 24
#define STANDARD_BIT 1
#define STANDARD_BIT_INDEX 26
#define STANDARD_BIT_MASK (STANDARD_BIT << STANDARD_BIT_INDEX)
#define COND_VALUE 0xE
#define COND_INDEX 28
#define COND_MASK (COND_VALUE << COND_INDEX)

uint32_t ldr_a(char** address);

uint32_t str_a(char** address);

uint32_t find_up_bit(int8_t offset);

#endif
