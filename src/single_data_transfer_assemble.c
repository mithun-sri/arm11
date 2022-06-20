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
    uint32_t cond;
    uint32_t i_bit;
    uint32_t p_bit;
    uint32_t u_bit;
    uint32_t l_bit = 1 << 20;
    char* address = str[2];

    if (strncmp(address, "=", 1) == 0){
        uint32_t value = strtoll(address, NULL, 0);
	if (value < 0xFF){
  	    uint8_t rd = atoi(str[1] + 1);
            printf("op : %s\n", str[2]);
            return mov_a(rd, str[2] + 1);
        } else {
		
        }
    } else{
        char *end;
        if ((end = strstr(address, "]")) == NULL){
            // Pre-indexed with offset
            printf("Pre-indexed with offset\n");
            char* rn_str = str[2] + 2;
            uint32_t rn = atoi(rn_str) << 16;
            char *offset_str = str[3];
            offset_str[strlen(offset_str) - 2] = '\0';
            int32_t s_offset;

            printf("offset_str: %s", offset_str);

            if (strncmp(offset_str, "0x", 2) == 0){
                u_bit = 1;
                s_offset = strtol(offset_str, NULL, 16);
                u_bit = 1 << 23;
            } else if (strncmp(offset_str, "-0x", 3) == 0){
                u_bit = 0;
                s_offset = strtol(offset_str + 1, NULL, 16);
            } else {
                s_offset = atoi(offset_str);
                u_bit = 1 << 23;
            }

            uint32_t offset = s_offset;

            cond = 0xE << 28;
            i_bit = 0 << 25;
            p_bit = 1 << 24;
            int rd = atoi(str[1] + 1);
            rd <<= 12;
            uint32_t rd_mask = *(uint32_t*)&rd;
	    uint32_t res = (p_bit | i_bit | cond | u_bit | l_bit | rn | rd_mask | offset | (1 << 26));
            return res;
        } else {
            // Pre-indexed with no offset
	    if ((end = strstr(address, "]")) != NULL){
		end++;
		if (strlen(end) > 1){
			// Post-indexed
			printf("Post-index");
			end++;
			uint32_t offset = atoi(end);
			char* rn_str = str[2] + 2;
			uint32_t rn = atoi(rn_str) << 16;
			cond = 0xE << 28;
			i_bit = 0 << 25;
			p_bit = 0 << 24;
			u_bit = 1 << 23;
			int rd = atoi(str[1] + 1);
			rd <<= 12;
			uint32_t rd_mask = *(uint32_t*)&rd;
			uint32_t res = (p_bit | i_bit | cond | u_bit | l_bit | rn | rd_mask | offset | (1 << 26));
			return res;
		} else {
			// Pre-indexed
	            	char* rn_str = str[2] + 2;
            		uint32_t rn = atoi(rn_str) << 16;
			i_bit = 0 << 25;
			p_bit = 1 << 24;
			u_bit = 1 << 23;
            		cond = 0xE << 28;
			uint32_t offset = 0;
            		int rd = atoi(str[1] + 1);
			rd <<= 12;
			uint32_t rd_mask = *(uint32_t*)&rd;
			uint32_t res = (p_bit | i_bit | cond | u_bit | l_bit | rn | rd_mask | offset | (1 << 26));
			return res;
		}
        }

      }}
      return 0;
}

uint32_t str_a(char** str){
    uint32_t cond;
    uint32_t i_bit = 1 << 25;
    uint32_t p_bit;
    uint32_t u_bit;
    uint32_t l_bit = 0 << 20;
    char* address = str[2];
    char *end;
    if ((end = strstr(address, "]")) == NULL){
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
        // Pre-indexed with no offset
        if ((end = strstr(address, "]")) != NULL){
            end++;
            if (str[3] != NULL){
                // Post-indexed
                end++;
                uint32_t offset = atoi(end);
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
            } else {
                // Pre-indexed
		        printf("Pre-indexed\n");
                char* rn_str = str[2] + 2;
                uint32_t rn = atoi(rn_str) << 16;
                p_bit = 1 << 24;
                u_bit = 1 << 23;
                cond = 0xE << 28;
                uint32_t offset = 0;
                int rd = atoi(str[1] + 1);
                rd <<= 12;
                uint32_t rd_mask = *(uint32_t*)&rd;
                uint32_t res = (p_bit | i_bit | cond | u_bit | l_bit | rn | rd_mask | offset | (1 << 26));
                return res;
            }
        }
    }
    return 0;    
}
