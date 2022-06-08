#ifndef SINGLE_DATA_TRANSFER_H
#define SINGLE_DATA_TRANSFER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "emulate.h"
#include 
#include "emulate_utilities.h"

int single_data_transfer(uint32_t instruction, struct REGISTERS* r, uint8_t *memory);

void perform_transfer(int l_bit, uint32_t new_address, uint32_t rd);

void register_write(uint32_t *dest, uint32_t value);

void memory_write(uint8_t *location, uint32_t value);

uint32_t compute_address(uint32_t value, uint32_t offset, int up_bit);

#endif
