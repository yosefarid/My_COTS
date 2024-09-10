#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

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

	/*ADC Interrupt State*/
	/*Enable the ADC interrupt "Requires Global interrupt to be on"*/
#if ADC_u8Interrupt == ON
	SET_BIT(ADCSRA,ADCSRA_ADIE);
	/*Disable the ADC interrupt*/
#elif ADC_u8Interrupt == OFF
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
#else
#error 		Wrong Interrupt State configration option
#endif

	/*Configure the Prescaler Division Factor*/

	/*Clear Prescaler Bits*/
	ADCSRA &= Prescaler_Bit_Mask;
	ADCSRA |= ADC_u8PrescalerDivisionFactor << Prescaler_Bit_Pos;

	/*Enable the ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

uint16 ADC_u8GetChannelReading(uint8 Copy_u8Channel)
{
	uint16 Local_u16Result;
	if(Copy_u8Channel < ADC_Channel_Limit)
	{
		/*Set ADC Channel*/
		ADMUX &= Channel_Bit_Mask;/*Clear Channel Bits*/
		ADMUX |= Copy_u8Channel;

		/*Start conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/*Polling with blocking on the conversion complete*/
		while(!(GET_BIT(ADCSRA ,ADCSRA_ADIF)));

		/*Clear the conversion complete*/
		SET_BIT(ADCSRA ,ADCSRA_ADIF);

		/*Get the conversion result*/
#if ADC_u8Resolution == _8_BIT
		Local_u16Result = ADCH;
#elif ADC_u8Resolution == _10_BIT
		Local_u16Result = ADC;
#else
#error 		Wrong Resolution configration option
#endif
	}
	else
	{
		Local_u16Result = ADC_u16Err;
	}
	return Local_u16Result;
}

