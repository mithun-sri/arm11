#ifndef SINGLE_DATA_TRANSFER_ASSEMBLE_H
#define SINGLE_DATA_TRANSFER_ASSEMBLE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "data_processing_assemble.h"
#include "assemble_utilities.h"

uint32_t ldr_a(char** address);

uint32_t str_a(char** address);

uint32_t find_up_bit(int8_t offset);

#endif
