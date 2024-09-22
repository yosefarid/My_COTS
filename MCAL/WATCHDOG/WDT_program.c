#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_register.h"
#include "WDT_interface.h"

void WDT_voidSetTime(uint8 Copy_u8Time)
{
	/*Clear prescaler Bits*/
	WDTCR &= 0b11111000;
	
	/*Set prescaler option*/
	WDTCR |= Copy_u8Time;
	
}

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR , WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	WDTCR = 0b00011000;
	WDTCR = 0u;
}

void WDT_voidReset(void)
{
	__asm volatile("WDR"); /*Inline assembly: Reset Watchdog*/
}