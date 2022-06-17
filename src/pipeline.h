#ifndef PIPELINE_H
#define PIPELINE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct data_pipeline{
	uint32_t fetched;
	uint32_t decoded;
	uint8_t fetch_set;
	uint8_t decode_set;
	uint8_t instr_set;
};

#endif
