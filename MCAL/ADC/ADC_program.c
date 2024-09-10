/*******************************************************************/
/***************     Author: Youssef_Farid		  *****************/
/***************     Layer: MCAL                  ****************/
/***************     ADC_program                  ***************/
/***************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

static void(*ADC_pvCallBackNotificationFunc)(void) = NULL;
static uint16* 	ADC_u16Result 	= NULL;
static uint8	ADC_u8BusyFlag 	= IDLE;
static uint8 	ADC_u8ChainFlag = 0u;
static uint8* 	ADC_ChannelArr 	= NULL;

void ADC_voidInit(void)
{
	/*Voltage reference configurations*/
	/*Set AREF as reference voltage*/
#if ADC_u8Voltage_Ref == AREF
	CLR_BIT(ADMUX,ADMUX_REFS1);
	CLR_BIT(ADMUX,ADMUX_REFS0);
	/*Set AVCC as reference voltage*/
#elif ADC_u8Voltage_Ref == AVCC
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
	/*Set internal 2.56V reference voltage*/
#elif ADC_u8Voltage_Ref == INTERNAL
	SET_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);

#else
#error 		Wrong voltage reference configration option
#endif

	/*Resolution configurations*/
	/*8 bit resolution*/
#if ADC_u8Resolution == _8_BIT
	SET_BIT(ADMUX,ADMUX_ADLAR);
	/*10 bit resolution*/
#elif ADC_u8Resolution == _10_BIT
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error 		Wrong Resolution configration option
#endif

	/*Conversion Mode*/
	/*Disable Auto trigger mode*/
#if ADC_u8Conv_Mode == Manual
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
	/*Enable Auto trigger mode*/
#elif ADC_u8Conv_Mode == Auto_Trigger
	SET_BIT(ADCSRA,ADCSRA_ADATE);

	/*Configure the Trigger Source option*/
	/*Clear Trigger Source Bits*/
	SFIOR &= Trigger_Source_Bit_Mask;
	SFIOR |= ADC_u8TriggerSource << Trigger_Source_Bit_Pos;

#else
#error 		Wrong Conversion Mode configration option
#endif

	/*Configure the Prescaler Division Factor*/

	/*Clear Prescaler Bits*/
	ADCSRA &= Prescaler_Bit_Mask;
	ADCSRA |= ADC_u8PrescalerDivisionFactor << Prescaler_Bit_Pos;

	/*Enable the ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel , uint16* Copy_pu16Result)
{
	uint8 Local_u8ErrState = OK;
	uint32 Local_u32Counter = 0u;

	if(Copy_pu16Result != NULL)
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Set ADC Channel*/
			ADMUX &= Channel_Bit_Mask;/*Clear Channel Bits*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Polling with blocking on the conversion complete on condition Timeout has not passed yet*/
			while(((GET_BIT(ADCSRA ,ADCSRA_ADIF)) == 0u) && (Local_u32Counter < ADC_u32TimeOut))
			{
				Local_u32Counter ++;
			}

			if(Local_u32Counter == ADC_u32TimeOut)
			{
				/*Timeout has passed without the flag being raised*/
				Local_u8ErrState = TIMEOUT_ERR;
			}
			else
			{
				/*The flag is raised before Timeout*/
				/*Clear the conversion complete*/
				SET_BIT(ADCSRA ,ADCSRA_ADIF);

				/*Get the conversion result*/
#if ADC_u8Resolution == _8_BIT
				*Copy_pu16Result = ADCH;
#elif ADC_u8Resolution == _10_BIT
				*Copy_pu16Result = ADC;
#else
#error 		Wrong Resolution configration option
#endif
			}

			/*ADC is now IDLE*/
			ADC_u8BusyFlag = IDLE;

		}
		else
		{
			Local_u8ErrState = BUSY_ERR;
		}

	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel , uint16* Copy_pu16Result , void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrState = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Convert the Local ADC Result into Global*/
			ADC_u16Result = Copy_pu16Result;

			/*Convert the Local ADC Call Back into Global*/
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Set ADC Channel*/
			ADMUX &= Channel_Bit_Mask;/*Clear Channel Bits*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable the ADC Conversion Complete interrupt "Requires Global interrupt to be on"*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}


	return Local_u8ErrState;
}

uint8 ADC_u8StartChainConvAsynch(uint8 Copy_u8NumOfChannels , uint8* Copy_u8Channels , uint16* Copy_pu16Results , void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrState = OK;

	if((Copy_pu16Results != NULL) && (Copy_pvNotificationFunc != NULL) && (Copy_u8Channels != NULL))
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Convert the Local ADC Number into Global*/
			ADC_u8ChainFlag = Copy_u8NumOfChannels;

			/*Convert the Local ADC Channel Array into Global*/
			ADC_ChannelArr = Copy_u8Channels;

			/*ADC is now IDLE*/
			ADC_u8BusyFlag = IDLE;

			/*Start the conversion*/
			ADC_u8StartConversionAsynch(*Copy_u8Channels , Copy_pu16Results , Copy_pvNotificationFunc);
		}
		else
		{
			Local_u8ErrState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

__attribute__((signal)) void __vector_16 (void);
void __vector_16 (void)
{
	/*Read Result*/
#if ADC_u8Resolution == _8_BIT
	*ADC_u16Result = ADCH;
#elif ADC_u8Resolution == _10_BIT
	*ADC_u16Result = ADC;
#else
#error 		Wrong Resolution configration option
#endif

	/*Disable Conversion Complete interrupt*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

	/*ADC is now IDLE*/
	ADC_u8BusyFlag = IDLE;

	/*Chain loop*/
	if(ADC_u8ChainFlag > 1)
	{
		ADC_u8ChainFlag --;
		ADC_u16Result ++;
		ADC_ChannelArr ++;
		ADC_u8StartConversionAsynch(*ADC_ChannelArr , ADC_u16Result , ADC_pvCallBackNotificationFunc);
	}
	else
	{
		/*Invoke the call back notification function*/
		if(ADC_pvCallBackNotificationFunc != NULL)
		{
			ADC_pvCallBackNotificationFunc();
		}
		else
		{
			/*Do nothing*/
		}
	}
}

