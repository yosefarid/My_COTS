#ifndef CLCD_PRIVATE_H
#define CLCD_PRIVATE_H

#define Max_num_numbers		10u
#define decimal_base		10u
#define zero				0u
#define Byte_Size			8u

#define FOUR_BIT			1
#define EIGHT_BI		T	2

#if CLCD_u8BIT_MODE == FOUR_BIT
static void SetHalfDataPort(uint8 Copy_u8Data);
#endif

static void voidSendEnablePulse(void);

#endif
