#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

typedef enum
{
	INT0, 
	INT1, 
	INT2
}IntChannel_t;

typedef enum
{
	LOW_LEVEL, 
	ON_CHANGE, 
	FALLING_EDGE, 
	RISING_EDGE
}SenseCtrl_t;

void EXTI_voidInit(void);

uint8 EXTI_u8SetSneseCtrl(IntChannel_t Copy_IntCh, SenseCtrl_t Copy_SenseCtrl);

uint8 EXTI_u8EnableIntChannel(IntChannel_t Copy_IntCh);

uint8 EXTI_u8DisableIntChannel(IntChannel_t Copy_IntCh);

uint8 EXTI_u8SetCallBack(IntChannel_t Copy_IntCh , void(*EXTI_pvCallBackFunc)(void));

#endif
