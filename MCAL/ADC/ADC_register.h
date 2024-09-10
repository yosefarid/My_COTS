/*******************************************************************/
/***************     Author: Youssef_Farid		  *****************/
/***************     Layer: MCAL                  ****************/
/***************     ADC_register                 ***************/
/***************************************************************/

#ifndef ADC_REGISTER_H
#define ADC_REGISTER_H

#define ADMUX 				*((volatile uint8*)0x27)	/*ADC Multiplexer Selection Register*/
#define ADMUX_REFS1			7u 							/*Reference selection BIT1*/
#define ADMUX_REFS0			6u							/*Reference selection BIT0*/
#define ADMUX_ADLAR			5u							/*Left Adjust Result*/


#define ADCSRA				*((volatile uint8*)0x26)	/*ADC Control and Status Register A*/
#define ADCSRA_ADEN			7u							/*ENABLE*/
#define ADCSRA_ADSC			6u                          /*Start conversion*/
#define ADCSRA_ADATE		5u                          /*Auto trigger enable*/
#define ADCSRA_ADIF			4u                          /*Interrupt flag*/
#define ADCSRA_ADIE			3u                          /*interrupt ENABLE*/

#define SFIOR				*((volatile uint8*)0x50)	/*Special FunctionIO Register*/

#define ADCH				*((volatile uint8*)0x25)	/*ADC Data High Register*/
#define ADCL				*((volatile uint8*)0x24)    /*ADC data low Register*/
#define ADC					*((volatile uint16*)0x24)	/*10 Bit Resolution*/



#endif
