#include "single_data_transfer_assemble.h"

uint32_t find_up_bit(int8_t offset){
    uint32_t up_bit;
    if (offset >= 0){
        up_bit = (1 << 23);
    } else {
        up_bit = 0;
    }
    return up_bit;
}

uint32_t convert(uint8_t n) {
  uint32_t bin = 0;
  int rem, i = 1;

  while (n!=0) {
    rem = n % 2;
    n /= 2;
    bin += rem * i;
    i *= 10;
  }

  return bin;
}

uint32_t ldr_a(char** str){
    if (str[3] == NULL){
        // Pre-index without offset or immediate
        // printf("Pre-index without offset or immediate\n");
        printf("rd: %s\n", str[1]);
        if (strncmp(str[2], "[", 1) == 0){
            // Pre-index without offset
            printf("%s\n", str[2]);
            char* value_str = str[2];
            value_str[strlen(value_str) - 2] = '\0';
            printf("%s\n", value_str);
            value_str += 1;
            uint32_t rn = atoi(value_str + 1) << 16;
            // printf("rn: %s", value_str + 1);
            uint32_t rd = atoi(str[1] + 1) << 12;
            uint32_t cond = 0xE << 28;
            uint32_t standard_bits = 1 << 26;
            uint32_t i_bit = 0;
            uint32_t p_bit = 1 << 24;
            uint32_t l_bit = 1 << 20;
            uint32_t offset = 0;
            uint32_t u_bit = 1 << 23;
            return (rn | rd | cond | standard_bits | u_bit | i_bit | p_bit | l_bit | offset);
        } else {
            // Immediate
            char* value_str = str[2];
            int32_t val;
            if (strncmp(value_str, "=", 1) == 0){
                // Hex value
                val = strtol(value_str + 1, NULL, 16);
                
            } else {
                val = atoi(value_str + 1);
            }

            if (val > 0xFF){
                // To do
                uint32_t u_bit;
                if (val >= 0){
                    u_bit = 1;
                } else {
                    u_bit = 0;
                }
            uint32_t value = (uint32_t) val;
            return (u_bit | value);
            } else {
                uint32_t rd = atoi(str[1] + 1) << 12;
                return mov_a(rd, value_str + 1);
            }
            
        }
    } else {
        printf("Pre-index with offset or post-index\n");
        printf("Str[3]: %s\n", str[3]);
        char* val_str = str[3];
        if (val_str[strlen(val_str) - 2] == ']'){
            // Pre-index with offset
            printf("Pre-index with offset\n");
            val_str[strlen(val_str) - 2] = '\0';
            int32_t s_offset;
            if (strncmp(val_str, "0x", 2) == 0){
                // Hex
                printf("Hex\n");
                s_offset = strtol(&val_str[2], NULL, 16);
            } else {
                // Immediate
                printf("Immediate\n");
                printf("s: %s", val_str);
                s_offset = atoi(val_str);
                // printf("Offset: %i\n", s_offset);
            }
            uint32_t u_bit;
            if (val_str[0] == '-'){
                val_str += 1;
                s_offset = strtol(&val_str[2], NULL, 16);
                u_bit = 0;
            } else {
                u_bit = 1 << 23;
            }
            printf("rn : %s", str[2] + 2);
            uint32_t rn = atoi(str[2] + 2) << 16;
            uint32_t rd = atoi(str[1] + 1) << 12;
            uint32_t cond = 0xE << 28;
            uint32_t standard_bits = 1 << 26;
            uint32_t i_bit = 0;
            uint32_t p_bit = 1 << 24;
            uint32_t l_bit = 1 << 20;
            uint32_t offset = s_offset;
            return (rn | rd | cond | standard_bits | i_bit | p_bit | l_bit | offset | u_bit);
        } else {
            printf("Post-index\n");
            // Post-index
        }
    }
    return 0;
}

uint32_t str_a(char** str){
    uint32_t cond;
    uint32_t i_bit = 1 << 25;
    uint32_t p_bit;
    uint32_t u_bit;
    uint32_t l_bit = 0 << 20;
    //char* address = str[2];
    char *end;
    if (str[3] == NULL){
        // Pre-index without offset
        printf("Post indexed\n");
        char* rn_str = str[2] + 2;
        uint32_t rn = atoi(rn_str) << 16;
        char *offset_str = str[3] + 1;
        offset_str[strlen(offset_str) - 2] = '\0';
        int32_t offset_s = strtol(offset_str, NULL, 16);
        uint32_t offset;
        if (offset_s >= 0){
            offset = offset_s;
            u_bit = 1 << 23;
        } else {
            offset = offset_s;
            u_bit = 0 << 23;
        }
        cond = 0xE << 28;
        p_bit = 1 << 24;
        int rd = atoi(str[1] + 1);
        rd <<= 12;
        uint32_t rd_mask = *(uint32_t*)&rd;
        uint32_t res = (p_bit | i_bit | cond | u_bit | l_bit | rn | rd_mask | offset | (1 << 26));
        return res;
    } else {
        if ((end = strstr(str[3], "]")) != NULL){
            end++;
                // Pre-indexed with offset
		        printf("Pre-indexed with offset\n");
                char* rn_str = str[2] + 2;
                printf("rn_str: %s\n", rn_str);
                uint32_t rn = atoi(rn_str) << 16;
                p_bit = 1 << 24;
                u_bit = 1 << 23;
                cond = 0xE << 28;
                char* offset_str = str[3];
                offset_str[strlen(offset_str) - 2] = '\0';
                // printf("Offset: %s", offset_str);
                uint32_t offset = atoi(offset_str);
                int rd = atoi(str[1] + 1);
                // printf("Rd: %i\n", rd);
                rd <<= 12;
                i_bit = 0 << 25;
                uint32_t rd_mask = *(uint32_t*)&rd;
                uint32_t res = (p_bit | i_bit | cond | u_bit | l_bit | rn | rd_mask | offset | (1 << 26));
                return res;
            }  else {
            // Post-indexed
                printf("%s\n", str[3]);
                uint32_t offset = atoi(str[3]);
                char* rn_str = str[2] + 2;
                uint32_t rn = atoi(rn_str) << 16;
                cond = 0xE << 28;
                p_bit = 0 << 24;
                u_bit = 1 << 23;
                int rd = atoi(str[1] + 1);
                rd <<= 12;
                uint32_t rd_mask = *(uint32_t*)&rd;
                uint32_t res = (p_bit | i_bit | cond | u_bit | l_bit | rn | rd_mask | offset | (1 << 26));
                return res;
        }
    }
    return 0;    
}