#define MAX_INSTR_COUNT 16384       //2^14 basically, (2^16/4) because 32bits = 4bytes
#define MAX_BYTES_IN_MEMORY 65536   //2^16

FILE *file;
long length;
uint32_t *arrayStart;

file = fopen("binFileName.bin", "rb");  // opens the binary file

arrayStart = (uint32_t *)calloc(MAX_INSTR_COUNT, MAX_BYTES_IN_MEMORY);  // allocate heap space
fread(arrayStart, MAX_INSTR_COUNT, 1, file);                            // read file into array
fclose(file);                                                           // close the file
