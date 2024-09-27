#ifndef USART_REGISTER_H
#define USART_REGISTER_H

#define UDR					*((volatile uint8*)0x2C)			/*USART I/O Data Register*/

#define UCSRA				*((volatile uint8*)0x2B)            /*USART Control and Status Register A*/
#define UCSRA_RXC			7u                                  /*USART Receive Complete*/
#define UCSRA_TXC			6u                                  /*USART Transmit Complete*/
#define UCSRA_UDRE			5u                                  /*USART Data Register Empty*/
	
#define UCSRB				*((volatile uint8*)0x2A)            /*USART Control and Status Register B*/
#define UCSRB_RXEN			4u                                  /*USART Receiver Enable*/
#define UCSRB_TXEN			3u                                  /*USART Transmitter Enable*/

#define UCSRC				*((volatile uint8*)0x40)            /*USART Control and Status Register C*/
#define UCSRC_URSEL			7u                                  /*USART Register Select*/
#define UCSRC_UMSEL			6u                                  /*USART Mode Select*/
#define UCSRC_UPM1			5u                                  /*USART Parity Mode BIT1*/
#define UCSRC_UPM0			4u                                  /*USART Parity Mode BIT0*/
#define UCSRC_USBS			3u                                  /*USART Stop Bit Select*/
#define UCSRC_UCSZ1			2u                                  /*USART Character Size BIT1*/
#define UCSRC_UCSZ0			1u                                  /*USART Character Size BIT0*/
#define UCSRC_UCPOL			0u                                  /*USART Clock Polarity*/
	
#define UBRRH				*((volatile uint8*)0x40)            /*USART Baud Rate Registers UBRRH*/
#define UBRRL				*((volatile uint8*)0x29)            /*USART Baud Rate Registers UBRRL*/

#endif