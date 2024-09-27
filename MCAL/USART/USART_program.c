#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_register.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"


void USART_voidInit(void)
{
	uint8 Local_u8UCSRC = 0u;
	uint16 Local_u16BaudRate;

	/*--------------------Choose the function of the USART--------------------*/
#if USART_Func == Transmit

	SET_BIT(UCSRB , UCSRB_TXEN);

#elif USART_Func == Transmit

	SET_BIT(UCSRB , UCSRB_RXEN);

#elif USART_Func == Receive_Transmit

	SET_BIT(UCSRB , UCSRB_TXEN);
	SET_BIT(UCSRB , UCSRB_RXEN);
#else
#error Wrong Function Mode Configuration
#endif

	/*--------------------Choose the Mode of the USART--------------------*/
#if USART_Mode == Asynchronous

	CLR_BIT(Local_u8UCSRC ,UCSRC_UMSEL);

#elif USART_Mode == Synchronous

	SET_BIT(Local_u8UCSRC ,UCSRC_UMSEL);

#else
#error  Wrong Mode Configuration
#endif

	/*--------------------Choose the Parity Mode of the USART--------------------*/
#if USART_ParityMode == Disabled

	CLR_BIT(Local_u8UCSRC , UCSRC_UPM1);
	CLR_BIT(Local_u8UCSRC , UCSRC_UPM0);

#elif USART_ParityMode == Even_Parity

	SET_BIT(Local_u8UCSRC , UCSRC_UPM1);
	CLR_BIT(Local_u8UCSRC , UCSRC_UPM0);

#elif USART_ParityMode == Odd_Parity

	SET_BIT(Local_u8UCSRC , UCSRC_UPM1);
	SET_BIT(Local_u8UCSRC , UCSRC_UPM0);

#else
#error Wrong Parity Mode Configuration
#endif


	/*--------------------Choose the Stop bits number of the USART--------------------*/
#if USART_StopBit == _1_bit

	CLR_BIT(Local_u8UCSRC ,UCSRC_USBS);

#elif USART_StopBit == _2_bit

	SET_BIT(Local_u8UCSRC ,UCSRC_USBS);

#else
#error  Wrong Stop bits Configuration
#endif


	/*--------------------Choose the Character Size of the USART--------------------*/
#if USART_CharSize == _9_bit

	/*Set character size*/
	SET_BIT(UCSRB , 2);
	SET_BIT(Local_u8UCSRC ,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC ,UCSRC_UCSZ0);

#else

	Local_u8UCSRC &= 0b11111001;
	Local_u8UCSRC |= USART_CharSize << 1;

#endif

	/*--------------------Choose the Clock Polarity of the USART--------------------*/
#if USART_ClockPolarity == Synchronous

#if USART_StopBit == Rising_Edge

	CLR_BIT(Local_u8UCSRC ,UCSRC_UCPOL);

#elif USART_ClockPolarity == Falling_Edge

	SET_BIT(Local_u8UCSRC ,UCSRC_UCPOL);

#else
#error  Wrong Clock Polarity Configuration
#endif

#endif

	/*Set register bit to select UCSRC*/
	SET_BIT(Local_u8UCSRC , UCSRC_URSEL);

	/*give the configuration to the register*/
	UCSRC = Local_u8UCSRC;

	/*Get the Baud Rate*/
	Local_u16BaudRate = (uint16) (((uint32)USART_ClockFrq / (uint32)((uint16)USART_BaudRate * 16UL) ) - 1);

	if(Local_u16BaudRate < u8OF_Value)
	{
		/*Set baud rate to the user Configuration */
		UBRRL = (uint8)Local_u16BaudRate;
	}
	else
	{
		/*Set baud rate to the user Configuration */
		UBRRL = (uint8)Local_u16BaudRate;
		UBRRH = Local_u16BaudRate >> 8;
	}
}

void USART_Transmit(uint8 Copu_u8Data)
{
	while(GET_BIT(UCSRA , UCSRA_UDRE) == 0);

	UDR = Copu_u8Data;
}

uint8 USART_u8Receive(void)
{
	while(GET_BIT(UCSRA , UCSRA_RXC) == 0);

	return UDR;
}
