/*******************************************************************/
/***************     Author: Youssef_Farid		  *****************/
/***************     Layer: MCAL                  ****************/
/***************     ADC_interface                ***************/
/***************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H


/**
 * @brief Initialize the ADC registers .
 *
 * This function initialize the ADC registers (ADMUX , ADCSRA , SFIOR) with a
 * list of configuration in ADC_config.h file .
 */
void ADC_voidInit(void);

/**
 * @brief Start ADC conversion on Synchronous mode .
 *
 * This function starts the ADC conversion and waits until the result is done
 * then assign it to the result pointer
 *
 * @param Copy_u8Channel: 	Receives the number of the channel wanted "usually from data sheet".
 * @param Copy_pu16Result: 	A pointer to receive the converted data from the ADC.
 * @return uint8 Returns:
 * '0u' on success,
 * '2u' if the pointer is NULL ,
 * '3u' if the timeout has passed and the interrupt flag did not rise
 * '4u' if the ADC is busy.
 */
uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel , uint16* Copy_pu16Result);

/**
 * @brief Start ADC conversion on Asynchronous mode .
 *
 * This function starts the ADC conversion and enables the ADC interrupt then later
 * the ISR function assign the value to the result pointer and call back the passed
 * function
 *
 * @note Requires the global interrupt to be on
 *
 * @param Copy_u8Channel:	 		Receives The number of the channel wanted "usually from data sheet".
 * @param Copy_pu16Result:	 		A pointer to receive the converted data from the ADC.
 * @param Copy_pvNotificationFunc: 	Receives the address(name) of the call back function
 * @return uint8 Returns:
 * '0u' on success,
 * '2u' if the pointer is NULL ,
 * '4u' if the ADC is busy.
 */
uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel , uint16* Copy_pu16Result , void(*Copy_pvNotificationFunc)(void));

/**
 * @brief Start ADC conversion on a chain of channels on Asynchronous mode .
 *
 * This function starts the ADC conversion on the channels passed *by order* and
 * returns their values in an *array*, and after all channels are converted, it
 * calls the ISR function.
 *
 * @note Requires the global interrupt to be on
 *
 * @param Copy_u8NumOfChannels:	 	The number of the channel wanted.
 * @param Copy_u8Channels:		 	Receives an array of numbers of the channel wanted "usually from data sheet".
 * @param Copy_pu16Result:		 	A array to receive the converted data from the ADC.
 * @param Copy_pvNotificationFunc: 	Receives the address(name) of the call back function
 * @return uint8 Returns:
 * '0u' on success,
 * '2u' if the pointer is NULL ,
 * '4u' if the ADC is busy.
 */
uint8 ADC_u8StartChainConvAsynch(uint8 Copy_u8NumOfChannels , uint8* Copy_u8Channels , uint16* Copy_pu16Results , void(*Copy_pvNotificationFunc)(void));

#endif
