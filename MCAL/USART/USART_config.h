#ifndef USART_CONFIG_H
#define USART_CONFIG_H

/*Select the function that you want from the USART, Options:	1- Receive
 * 																2- Transmit
 * 																3- Receive_Transmit
 * 	*/
#define USART_Func										Receive_Transmit

/*Select the USART Mode, Options:								1- Asynchronous
 * 																2- Synchronous
 * 	*/
#define USART_Mode										Asynchronous

/*Select the USART Parity Mode, Options:						1- Disabled
 * 																2- Even_Parity
 * 																3- Odd_Parity
 * 	*/
#define USART_ParityMode								Disabled

/*Select the USART stop bits configuration, Options:			1- _1_bit
 * 																2- _2_bit
 * 	*/
#define USART_StopBit									_1_bit

/*Select the USART Char Size, Options:							1- _5_bit
 * 																2- _6_bit
 * 																3- _7_bit
 * 																4- _8_bit
 * 																5- _9_bit
 * 	*/
#define USART_CharSize									_8_bit


#if USART_Mode == Synchronous

	/*Select the USART Clock Polarity, Options:					1- Rising_Edge
	 * 															2- Falling_Edge
	 * 	*/
	#define USART_ClockPolarity								Rising_Edge

#endif

#define USART_ClockFrq									16000000
#define USART_BaudRate									9600

#endif
