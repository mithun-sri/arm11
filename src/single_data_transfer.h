#ifndef SINGLE_DATA_TRANSFER_H
#define SINGLE_DATA_TRANSFER_H

#include <stdlib.h>
#include <stdio.h>
#include "emulate_architecture.h"
#include "emulate_utilities.h"
#include "data_processing.h"

struct registers single_data_transfer(uint32_t instruction, struct registers r);

struct registers perform_transfer(struct registers r, int l_bit, uint32_t new_address, uint8_t rd);

struct registers register_write(struct registers r, uint8_t dest, uint32_t value);

void memory_write(uint8_t *location, uint32_t value);

uint32_t compute_address(uint32_t value, uint32_t offset, int up_bit);

#endif
