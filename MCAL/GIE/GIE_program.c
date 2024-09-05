#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_register.h"

void GIE_voidEnableGlobal(void)
{
	__asm volatile("SEI"); /*Inline assembly: Set I-BIT*/
	/*SET_BIT(SREG , SREG_I);*/
}

void GIE_voidDisableGlobal(void)
{
	__asm volatile("CLI"); /*Inline assembly: Clr I-BIT*/
	/*SET_BIT(SREG , SREG_I);*/
}

