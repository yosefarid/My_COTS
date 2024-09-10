#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/*Voltage reference options*/
#define AREF							1u
#define AVCC							2u
#define INTERNAL						3u

/*Resolution options*/
#define _8_BIT							1u
#define _10_BIT							2u

/*Conversion mode options*/
#define Manual							1u
#define Auto_Trigger	   			 	2u

/*ADC Interrupt State options*/
#define ON           	  				1u
#define OFF         	    			2u

/*Prescaler Division Factor options*/
#define Division_by_2       			1u
#define Division_by_4       			2u
#define Division_by_8       			3u
#define Division_by_16      			4u
#define Division_by_32      			5u
#define Division_by_64      			6u
#define Division_by_128     			7u
#define Prescaler_Bit_Mask				0b11111000
#define Prescaler_Bit_Pos				0u

/*Trigger Source options*/
#if ADC_u8Conv_Mode == Auto_Trigger

#define Free_Running_mode              	0u
#define Analog_Comparator              	1u
#define External_Interrupt_Request_0   	2u
#define Counter0_Compare_Match         	3u
#define Counter0_Overflow              	4u
#define Counter_Compare_Match B        	5u
#define Counter1_Overflow              	6u
#define Counter1_Capture_Event      	7u
#define Trigger_Source_Bit_Mask			0b00011111
#define Trigger_Source_Bit_Pos			5u

#endif

#define Channel_Bit_Mask				0b11100000
#define	ADC_u16Err						1024
#define ADC_Channel_Limit				64

#endif
