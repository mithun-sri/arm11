#ifndef SPECIAL_ASSEMBLE_H
#define SPECIAL_ASSEMBLE_H
#include "data_processing_assemble.h"

#define HALT 0x00000000

uint32_t lsl_a(uint8_t rn, uint8_t op2);

uint32_t andeq_a();

#endif