#include "data_processing.h"

int get_bit(uint32_t content) 
{
	return content > 0 ? 1 : 0;
}

Operand2 logical_left_shift(uint8_t shift_amount, uint32_t content) 
{
	Operand2 res;
	res.value = (uint32_t) (content << shift_amount);
	res.carry = get_bit(1 << (NUM_REGISTER_BITS - shift_amount) & content); 

	return res; 
}

Operand2 logical_right_shift(uint8_t shift_amount, uint32_t content)
{
	Operand2 res;
	res.value = (uint32_t) (content >> shift_amount);
	res.carry = get_bit(1 << shift_amount & content); 

	return res; 
}
	
Operand2 arithmetic_right_shift(uint8_t shift_amount, uint32_t content) 
{
	Operand2 res = logical_right_shift(shift_amount, content);
	res.value = res.value // Perform extract bit and OR 
}

Operand2 rotate_right(uint8_t shift_amount, uint32_t content) 
{

}
