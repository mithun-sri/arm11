include <stdlib.h>
include <stdio.h>

int pipeline(uint8_t *memory){
	uint8_t *ptr = *memory;
	uint32_t decoded = 0;
	uint8_t fetched = 0;
	while (true){
		fetched = fetch(&ptr);
		reg.pc += 4;
		decoded = decode(fetched);
		reg.pc += 4;
		if (decoded == 0){
			break;
		}


