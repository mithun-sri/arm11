#include "data_processing_utilities.h"

uint8_t get_bit(uint32_t content) {
	return content > 0 ? 1 : 0;
}

uint32_t create_contiguous_mask(uint8_t num_bits) {
	uint32_t mask = 1;
	for (int i=0; i<num_bits-1; i++) {
		mask = mask | mask << 1;
	}
	return mask;
}
