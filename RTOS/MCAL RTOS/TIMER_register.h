#ifndef TIMER_REGISTER_H
#define TIMER_REGISTER_H
///////////////////////////////////// 			TIMER 0 			//////////////////////////////////////////////////////
#define TCCR0				*((volatile uint8*)0x53)		/*Timer/Counter0 Control Register*/
#define TCCR0_FOC0			7u								/*Force Output Compare*/
#define TCCR0_WGM00			6u								/*Waveform Generation Mode BIT 0*/
#define TCCR0_COM01			5u								/*Compare Match Output Mode BIT 1*/
#define TCCR0_COM00			4u								/*Compare Match Output Mode BIT 0*/
#define TCCR0_WGM01			3u								/*Waveform Generation Mode BIT 1*/

#define TCNT0				*((volatile uint8*)0x52)		/*Timer/Counter Register*/

#define OCR0				*((volatile uint8*)0x5C)		/*Output Compare Register*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////// 			TIMER 1 			//////////////////////////////////////////////////////
#define TCCR1A				*((volatile uint8*)0x4F)		/*Timer/Counter1 Control Register A*/
#define TCCR1A_COM1A1		7u								/*Compare Output Mode for Channel A BIT 1*/
#define TCCR1A_COM1A0		6u								/*Compare Output Mode for Channel A BIT 0*/
#define TCCR1A_COM1B1		5u								/*Compare Output Mode for Channel B BIT 1*/
#define TCCR1A_COM1B0		4u								/*Compare Output Mode for Channel B BIT 0*/
#define TCCR1A_FOC1A		3u								/*Force Output Compare for Channel A*/
#define TCCR1A_FOC1B		2u								/*Force Output Compare for Channel B*/
#define TCCR1A_WGM11		1u								/*Waveform Generation Mode BIT 1*/
#define TCCR1A_WGM10		0u								/*Waveform Generation Mode BIT 0*/

#define TCCR1B				*((volatile uint8*)0x4E)		/*Timer/Counter1 Control Register*/
#define TCCR1B_ICNC1		7u								/*Input Capture Noise Canceler*/
#define TCCR1B_ICES1		6u								/*Input Capture Edge Select*/
#define TCCR1B_WGM13		4u								/*Timer/Counter Interrupt Mask Register*/
#define TCCR1B_WGM12		3u								/*Timer/Counter Interrupt Mask Register*/

#define TCNT1				*((volatile uint16*)0x4C)		/*Timer/Counter1 – TCNT1H and TCNT1L*/

#define OCR1A				*((volatile uint16*)0x4A)		/*Output Compare Register 1 A – OCR1AH and OCR1AL*/

#define OCR1B				*((volatile uint16*)0x48)		/*Output Compare Register 1 B – OCR1BH and OCR1BL*/

#define ICR1				*((volatile uint16*)0x46)		/*Input Capture Register 1 – ICR1H and ICR1L*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////// 			TIMER 2 			/////////////////////////////////////////////////////
#define TCCR2				*((volatile uint8*)0x45)		/*Timer/Counter2 Control Register*/
#define TCCR2_FOC2			7u								/*Force Output Compare*/
#define TCCR2_WGM20			6u								/*Waveform Generation Mode BIT 0*/
#define TCCR2_COM21			5u								/*Compare Match Output Mode BIT 1*/
#define TCCR2_COM20			4u								/*Compare Match Output Mode BIT 0*/
#define TCCR2_WGM21			3u								/*Waveform Generation Mode BIT 1*/

#define TCNT2				*((volatile uint8*)0x44)		/*Timer/Counter Register*/

#define OCR2				*((volatile uint8*)0x43)		/*Output Compare Register*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////// 			INTERRUPT_CONFIG 			//////////////////////////////////////////////
#define TIMSK				*((volatile uint8*)0x59)		/*Timer/Counter Interrupt Mask Register*/
#define TIMSK_OCIE2			7u								/*Timer/Counter2 Output Compare Match Interrupt Enable*/
#define TIMSK_TOIE2			6u								/*Timer/Counter2 Overflow Interrupt Enable*/
#define TIMSK_TICIE1		5u								/*Timer/Counter1, Input Capture Interrupt Enable*/
#define TIMSK_OCIE1A		4u								/*Timer/Counter1, Output Compare A Match Interrupt Enable*/
#define TIMSK_OCIE1B		3u								/*Timer/Counter1, Output Compare B Match Interrupt Enable*/
#define TIMSK_TOIE1			2u								/*Timer/Counter1, Overflow Interrupt Enable*/
#define TIMSK_OCIE0			1u								/*Timer/Counter0 Output Compare Match Interrupt Enable*/
#define TIMSK_TOIE0			0u								/*Timer/Counter0 Overflow Interrupt Enable*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
