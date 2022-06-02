#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#define NUM_EXPECTED_ARGS 2
#define NUMBER_MEM_LOCATIONS 65536

struct registers {
	uint32_t gen_regs[13];
	uint32_t sp;
	uint32_t lp;
	uint32_t pc;
	uint32_t cpsr;
};

int main(int argc, char **argv) {	
	
	assert(argc == 2);
	
	FILE *instructFile;
	if ((instructFile = fopen(argv[1], "rb")) == NULL) {
		perror("Error opening file.");
		exit(EXIT_FAILURE);
	}
	
	uint8_t *memory = calloc(NUMBER_MEM_LOCATIONS, sizeof(uint8_t));

	size_t size = fread(memory, NUMBER_MEM_LOCATIONS, 1, instructFile);
	if (ferror(instructFile)) {
		printf("File size: %lu", size);
		perror("Error reading file.");
		exit(EXIT_FAILURE);
	}
	fclose(instructFile);
}
