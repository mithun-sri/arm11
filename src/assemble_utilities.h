#include <stdint.h>
#include <stdio.h>

#define BYTE_ZERO_MASK 0xff
#define BYTE_ONE_MASK 0xff00
#define BYTE_TWO_MASK 0xff0000
#define BYTE_THREE_MASK 0xff000000
#define ONE_BYTE_SHIFT 0x8
#define THREE_BYTE_SHIFT 0x24


uint32_t big_endian_to_little_endian(uint32_t little_endian);

