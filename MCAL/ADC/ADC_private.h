/*******************************************************************/
/***************     Author: Youssef_Farid		  *****************/
/***************     Layer: MCAL                  ****************/
/***************     ADC_private                  ***************/
/***************************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/**
 * @brief Macros to set Voltage reference options.
 */
#define AREF							1u
#define AVCC							2u
#define INTERNAL						3u

/**
 * @brief Macros to set Resolution options.
 */
#define _8_BIT							1u
#define _10_BIT							2u

/**
 * @brief Macros to set Conversion mode options.
 */
#define Manual							1u
#define Auto_Trigger	   			 	2u

/**
 * @brief Macros to set Prescaler Division Factor options and initialization.
 */
#define Division_by_2       			1u
#define Division_by_4       			2u
#define Division_by_8       			3u
#define Division_by_16      			4u
#define Division_by_32      			5u
#define Division_by_64      			6u
#define Division_by_128     			7u
#define Prescaler_Bit_Mask				0b11111000
#define Prescaler_Bit_Pos				0u

/**
 * @brief Macros to set Trigger Source options and initialization.
 */
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

/**
 * @brief Macro to clear the channel bits.
 */
#define Channel_Bit_Mask				0b11100000

/**
 * @brief Macros for busy ADC .
 */
#define IDLE							0u
#define BUSY							1u

#endif
