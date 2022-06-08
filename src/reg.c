#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SPACE 65536

FILE* fPtr;

struct REGISTERS {
    uint32_t general[13], sp, lr, pc, cpsr; 
};

int fileReader(FILE* fPtr) {
    if (fPtr == NULL) {
        printf("Invalid file type: Could not open file\n");
        exit(EXIT_FAILURE);
    }
    
    // start reading at beginning of file - CHECK IF NEEDED
    fseek(fPtr, 0, SEEK_SET);

    uint8_t *memory = calloc(MAX_SPACE, sizeof(uint8_t));
    size_t sizeOfFile = fread(memory, MAX_SPACE, 1, fPtr);

    fclose(fPtr);
    exit(EXIT_SUCCESS);  
}

int main(void) {
    fPtr = fopen("filename.bin", "rb"); // replace filename with test filename
    struct REGISTERS r = {.general = {0,0,0,0,0,0,0,0,0,0,0,0,0}, .sp = 0, .lr = 0, .pc = 0, .cpsr = 0};

    fileReader(fPtr); 
}
