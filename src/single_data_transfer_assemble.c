#include "single_data_transfer_assemble.h"

uint32_t find_up_bit(int8_t offset){
    uint32_t up_bit;
    if (offset >= 0){
        up_bit = (1 << UP_BIT_INDEX);
    } else {
        up_bit = 0;
    }
    return up_bit;
}

uint32_t ldr_a(char** str){
    if (str[3] == NULL){
        // Pre-index without offset or immediate
        if (strncmp(str[2], "[", 1) == 0){
            // Pre-index without offset
            char* value_str = str[2];
            value_str[strlen(value_str) - 2] = '\0';
            value_str += 1;
            uint32_t rn = atoi(value_str + 1) << 16;
            uint32_t rd = atoi(str[1] + 1) << 12;
            uint32_t i_bit = 0;
            uint32_t p_bit = 1 << P_BIT_INDEX;
            uint32_t l_bit = 1 << L_BIT_INDEX;
            uint32_t offset = 0;
            uint32_t u_bit = 1 << UP_BIT_INDEX;
            return (rn | rd | COND_MASK | STANDARD_BIT_MASK | u_bit | i_bit | p_bit | l_bit | offset);
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
        char* val_str = str[3];
        if (val_str[strlen(val_str) - 2] == ']'){
            // Pre-index with offset
            val_str[strlen(val_str) - 2] = '\0';
            int32_t s_offset;
            if (strncmp(val_str, "0x", 2) == 0){
                // Hex
                s_offset = strtol(&val_str[2], NULL, 16);
            } else {
                // Immediate
                s_offset = atoi(val_str);
            }
            uint32_t u_bit;
            if (val_str[0] == '-'){
                val_str += 1;
                s_offset = strtol(&val_str[2], NULL, 16);
                u_bit = 0;
            } else {
                u_bit = 1 << UP_BIT_INDEX;
            }
            uint32_t rn = atoi(str[2] + 2) << 16;
            uint32_t rd = atoi(str[1] + 1) << 12;
            uint32_t i_bit = 0;
            uint32_t p_bit = 1 << P_BIT_INDEX;
            uint32_t l_bit = 1 << L_BIT_INDEX;
            uint32_t offset = s_offset;
            return (rn | rd | COND_MASK | STANDARD_BIT_MASK | i_bit | p_bit | l_bit | offset | u_bit);
        } else {
            // Post-index
            uint32_t offset = atoi(str[3]);
            uint32_t i_bit = 1 << 25;
            uint32_t l_bit = 1 << L_BIT_INDEX;
            char* rn_str = str[2] + 2;
            uint32_t rn = atoi(rn_str) << 16;
            uint32_t p_bit = 0 << P_BIT_INDEX;
            uint32_t u_bit = 1 << UP_BIT_INDEX;
            int rd = atoi(str[1] + 1);
            rd <<= 12;
            uint32_t rd_mask = *(uint32_t*)&rd;
            uint32_t res = (p_bit | i_bit | COND_MASK | u_bit | l_bit | rn | rd_mask | offset | STANDARD_BIT_MASK);
            return res;
        }
    }
    return 0;
}

uint32_t str_a(char** str){
    uint32_t i_bit = 1 << 25;
    uint32_t p_bit;
    uint32_t u_bit;
    uint32_t l_bit = 0 << L_BIT_INDEX;
    //char* address = str[2];
    char *end;
    if (str[3] == NULL){
        // Pre-index without offset
        char* rn_str = str[2] + 2;
        uint32_t rn = atoi(rn_str) << 16;
        char *offset_str = str[3] + 1;
        offset_str[strlen(offset_str) - 2] = '\0';
        int32_t offset_s = strtol(offset_str, NULL, 16);
        uint32_t offset;
        if (offset_s >= 0){
            offset = offset_s;
            u_bit = 1 << UP_BIT_INDEX;
        } else {
            offset = offset_s;
            u_bit = 0 << UP_BIT_INDEX;
        }
        p_bit = 1 << P_BIT_INDEX;
        int rd = atoi(str[1] + 1);
        rd <<= 12;
        uint32_t rd_mask = *(uint32_t*)&rd;
        uint32_t res = (p_bit | i_bit | COND_MASK | u_bit | l_bit | rn | rd_mask | offset | STANDARD_BIT_MASK);
        return res;
    } else {
        if ((end = strstr(str[3], "]")) != NULL){
            end++;
                // Pre-indexed with offset
                char* rn_str = str[2] + 2;
                uint32_t rn = atoi(rn_str) << 16;
                p_bit = 1 << P_BIT_INDEX;
                u_bit = 1 << UP_BIT_INDEX;
                char* offset_str = str[3];
                offset_str[strlen(offset_str) - 2] = '\0';
                // printf("Offset: %s", offset_str);
                uint32_t offset = atoi(offset_str);
                int rd = atoi(str[1] + 1);
                // printf("Rd: %i\n", rd);
                rd <<= 12;
                i_bit = 0 << 25;
                uint32_t rd_mask = *(uint32_t*)&rd;
                uint32_t res = (p_bit | i_bit | COND_MASK | u_bit | l_bit | rn | rd_mask | offset | STANDARD_BIT_MASK);
                return res;
            }  else {
            // Post-indexed
                uint32_t offset = atoi(str[3]);
                char* rn_str = str[2] + 2;
                uint32_t rn = atoi(rn_str) << 16;
                p_bit = 0 << P_BIT_INDEX;
                u_bit = 1 << UP_BIT_INDEX;
                int rd = atoi(str[1] + 1);
                rd <<= 12;
                uint32_t rd_mask = *(uint32_t*)&rd;
                uint32_t res = (p_bit | i_bit | COND_MASK | u_bit | l_bit | rn | rd_mask | offset | STANDARD_BIT_MASK);
                return res;
        }
    }
    return 0;    
}