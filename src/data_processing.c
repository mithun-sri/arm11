#include "data_processing.h"

Operand2 logical_left_shift(uint8_t shift_amount, uint32_t content) 
{
	Operand2 res;
	res.value = (uint32_t) (content << shift_amount);
	res.carry = 1 << (NUM_REGISTER_BITS - shift_amount) & content > 0 ? 1 : 0;

	return res; 
}

Operand2 logical_right_shift(uint8_t shift_amount, uint32_t content)
{
	
}
	
Operand2 arithmetic_right_shift(uint8_t shift_amount, uint32_t content) 
{
	
}

Operand2 rotate_right(uint8_t shift_amount, uint32_t content) 
{

}
