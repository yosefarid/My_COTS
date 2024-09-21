#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "TIMER_register.h"
#include "TIMER_private.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"

static void (*Timer_pvCallBackFunc[8])(void) = { NULL };

////////////////////////////////////			Timer initialization			///////////////////////////////////////////

uint8 TIMER0_u8Init(TIM_0_2_t* Copy_Configuration)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_Configuration != NULL)
	{
		/*Choosing the waveform generation mode*/
		if(Copy_Configuration -> Wave_mode == Normal)
		{
			/*Choosing Normal Mode*/
			CLR_BIT(TCCR0 , TCCR0_WGM00);
			CLR_BIT(TCCR0 , TCCR0_WGM01);

		}
		else if(Copy_Configuration -> Wave_mode == PWM_Phase_Correct)
		{
			/*Choosing PWM_Phase_Correct Mode*/
			SET_BIT(TCCR0 , TCCR0_WGM00);
			CLR_BIT(TCCR0 , TCCR0_WGM01);

			/*Clear the Compare Output bits*/
			TCCR0 &= 0b11001111;
			/*Set compare output bits to the desired mode*/
			TCCR0 |= ((Copy_Configuration -> Compare_PWM_Mode) << 4);

		}
		else if(Copy_Configuration -> Wave_mode == CTC)
		{
			/*Choosing CTC Mode*/
			CLR_BIT(TCCR0 , TCCR0_WGM00);
			SET_BIT(TCCR0 , TCCR0_WGM01);

			/*Clear the Compare Output bits*/
			TCCR0 &= 0b11001111;
			/*Set compare output bits to the desired mode*/
			TCCR0 |= ((Copy_Configuration -> Compare_Mode) << 4);

		}
		else if(Copy_Configuration -> Wave_mode == Fast_PWM)
		{
			/*Choosing Fast_PWM Mode*/
			SET_BIT(TCCR0 , TCCR0_WGM00);
			SET_BIT(TCCR0 , TCCR0_WGM01);

			/*Clear the Compare Output bits*/
			TCCR0 &= 0b11001111;
			/*Set compare output bits to the desired mode*/
			TCCR0 |= ((Copy_Configuration -> Compare_PWM_Mode) << 4);

		}
		else
		{
			Local_u8ErrState = NOK;
		}

		/*Clear the Prescaler bits*/
		TCCR0 &= 0b11111000;
		/*Set Prescaler bits to the desired mode*/
		TCCR0 |= Copy_Configuration -> Prescaler;
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

uint8 TIMER1_u8Init(TIM_1_t* Copy_Configuration)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_Configuration != NULL)
	{
/////////////////////////////////////////////////*Setting the waveform mode*/////////////////////////////////////////////////

		/*Clear wave generation bits*/
		TCCR1A &= 0b11111100;
		TCCR1B &= 0b11100111;

		/*Separating the bits of the configuration for each register*/
		uint8 Local_u8First_Half = Copy_Configuration -> Compare_PWM_Mode & 0b00000011;
		uint8 Local_u8Second_Half = ((Copy_Configuration -> Compare_PWM_Mode & 0b00001100) << 1);

		/*Set the wave form bits for the desired mode*/
		TCCR1A |= Local_u8First_Half;
		TCCR1B |= Local_u8Second_Half;

/////////////////////////////////////////////////*Set Compare Match bits*/////////////////////////////////////////////////

		if(Copy_Configuration -> Channel == Channel_A)
		{

			if(Copy_Configuration -> Wave_mode == CTC_OCR || Copy_Configuration -> Wave_mode == CTC_ICR)
			{
				/*Clear the Compare Output bits*/
				TCCR0 &= 0b00111111;
				/*Set compare output bits to the desired mode*/
				TCCR0 |= ((Copy_Configuration -> Compare_Mode) << 6);
			}
			else if(Copy_Configuration -> Wave_mode == Normal_COM)
			{
				/*Leave it for default*/
			}
			else
			{
				/*Clear the Compare Output bits*/
				TCCR0 &= 0b00111111;
				/*Set compare output bits to the desired mode*/
				TCCR0 |= ((Copy_Configuration -> Compare_PWM_Mode) << 6);
			}

		}
		else if(Copy_Configuration -> Channel == Channel_B)
		{

			if(Copy_Configuration -> Wave_mode == CTC_OCR || Copy_Configuration -> Wave_mode == CTC_ICR)
			{
				/*Clear the Compare Output bits*/
				TCCR0 &= 0b11001111;
				/*Set compare output bits to the desired mode*/
				TCCR0 |= ((Copy_Configuration -> Compare_Mode) << 4);
			}
			else if(Copy_Configuration -> Wave_mode == Normal_COM)
			{
				/*Leave it for default*/
			}
			else
			{
				/*Clear the Compare Output bits*/
				TCCR0 &= 0b11001111;
				/*Set compare output bits to the desired mode*/
				TCCR0 |= ((Copy_Configuration -> Compare_PWM_Mode) << 4);
			}

		}
		else
		{
			Local_u8ErrState = NOK;
		}

/////////////////////////////////////////////////*Set Prescaler*/////////////////////////////////////////////////

		/*Clear the Prescaler bits*/
		TCCR1B &= 0b11111000;
		/*Set Prescaler bits to the desired mode*/
		TCCR1B |= Copy_Configuration -> Prescaler;
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

uint8 TIMER2_u8Init(TIM_0_2_t* Copy_Configuration)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_Configuration != NULL)
	{
		/*Choosing the waveform generation mode*/
		if(Copy_Configuration -> Wave_mode == Normal)
		{
			/*Choosing Normal Mode*/
			CLR_BIT(TCCR2 , TCCR2_WGM20);
			CLR_BIT(TCCR2 , TCCR2_WGM21);

		}
		else if(Copy_Configuration -> Wave_mode == PWM_Phase_Correct)
		{
			/*Choosing PWM_Phase_Correct Mode*/
			SET_BIT(TCCR2 , TCCR2_WGM20);
			CLR_BIT(TCCR2 , TCCR2_WGM21);

			/*Clear the Compare Output bits*/
			TCCR2 &= 0b11001111;
			/*Set compare output bits to the desired mode*/
			TCCR2 |= ((Copy_Configuration -> Compare_PWM_Mode) << 4);

		}
		else if(Copy_Configuration -> Wave_mode == CTC)
		{
			/*Choosing CTC Mode*/
			CLR_BIT(TCCR2 , TCCR2_WGM20);
			SET_BIT(TCCR2 , TCCR2_WGM21);

			/*Clear the Compare Output bits*/
			TCCR2 &= 0b11001111;
			/*Set compare output bits to the desired mode*/
			TCCR2 |= ((Copy_Configuration -> Compare_Mode) << 4);

		}
		else if(Copy_Configuration -> Wave_mode == Fast_PWM)
		{
			/*Choosing Fast_PWM Mode*/
			SET_BIT(TCCR2 , TCCR2_WGM20);
			SET_BIT(TCCR2 , TCCR2_WGM21);

			/*Clear the Compare Output bits*/
			TCCR2 &= 0b11001111;
			/*Set compare output bits to the desired mode*/
			TCCR2 |= ((Copy_Configuration -> Compare_PWM_Mode) << 4);

		}
		else
		{
			Local_u8ErrState = NOK;
		}

		/*Clear the Prescaler bits*/
		TCCR2 &= 0b11111000;
		/*Set Prescaler bits to the desired mode*/
		TCCR2 |= Copy_Configuration -> Prescaler;
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////			Helper FUNC			///////////////////////////////////////////////////////
void TIMER_void_Int_Enable(uint8 Copy_u8_INT)
{
	SET_BIT(TIMSK , Copy_u8_INT);
}

void TIMER_void_Int_Disable(uint8 Copy_u8_INT)
{
	CLR_BIT(TIMSK , Copy_u8_INT);
}

uint8 TIMER_u8SetCallBack(uint8 Copy_uu8IntSource , void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrState = OK;

	if(Copy_pvCallBackFunc !=NULL)
	{
		Timer_pvCallBackFunc[Copy_uu8IntSource] = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

void TIMER_voidSetPreloadValue(uint16 Copy_u16PreloadVal , volatile  uint8* Copy_pu8TIMER)
{
	*Copy_pu8TIMER = Copy_u16PreloadVal;
}

void TIMER_voidSetCompareMatchValue(uint16 Copy_u16CompMatchVal ,volatile  uint8* Copy_pu8TIMER)
{
	*Copy_pu8TIMER = Copy_u16CompMatchVal;
}

void TIMER_voidSetInputCaptureValue(uint16 Copy_u8CompMatchVal)
{
	ICR1 = Copy_u8CompMatchVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////			ISR FUNC			///////////////////////////////////////////////////////
/*Timer0 ISR Overflow*/
__attribute__((signal)) void __vector_11 (void);
void __vector_11 (void)
{
	if(Timer_pvCallBackFunc[TIMER0_OVF_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER0_OVF_INT]();
	}
}

/*Timer0 ISR Compare Match*/
__attribute__((signal)) void __vector_10 (void);
void __vector_10 (void)
{
	if(Timer_pvCallBackFunc[TIMER0_OC_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER0_OC_INT]();
	}
}

/*Timer1 ISR Overflow*/
__attribute__((signal)) void __vector_9 (void);
void __vector_9 (void)
{
	if(Timer_pvCallBackFunc[TIMER1_OVF_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER1_OVF_INT]();
	}
}

/*Timer1 ISR Compare Match Channel B*/
__attribute__((signal)) void __vector_8 (void);
void __vector_8 (void)
{
	if(Timer_pvCallBackFunc[TIMER1_B_OC_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER1_B_OC_INT]();
	}
}

/*Timer1 ISR Compare Match Channel A*/
__attribute__((signal)) void __vector_7 (void);
void __vector_7 (void)
{
	if(Timer_pvCallBackFunc[TIMER1_A_OC_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER1_A_OC_INT]();
	}
}

/*Timer1 ISR Capture Event*/
__attribute__((signal)) void __vector_6 (void);
void __vector_6 (void)
{
	if(Timer_pvCallBackFunc[TIMER0_ICU_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER0_ICU_INT]();
	}
}

/*Timer2 ISR Overflow*/
__attribute__((signal)) void __vector_5 (void);
void __vector_5 (void)
{
	if(Timer_pvCallBackFunc[TIMER2_OVF_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER2_OVF_INT]();
	}
}

/*Timer2 ISR Compare Match*/
__attribute__((signal)) void __vector_4 (void);
void __vector_4 (void)
{
	if(Timer_pvCallBackFunc[TIMER2_OC_INT] != NULL)
	{
		Timer_pvCallBackFunc[TIMER2_OC_INT]();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
