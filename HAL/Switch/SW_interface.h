#ifndef SW_INTERFACE_H
#define SW_INTERFACE_H

#include "DIO_interface.h"

typedef struct
{
	uint8 SW_u8PullType;
	uint8 SW_u8Port;
	uint8 SW_u8Pin;
}SW_t;

#define SW_u8PullUp					1u
#define SW_u8PullDown				0u

#define SW_u8SinkPressed			1u
#define SW_u8SinkNotPressed			0u
#define SW_u8SourcePressed			0u
#define SW_u8SourceNotPressed		1u

uint8 SW_u8GetState(SW_t * Copy_pswComponent , uint8 * Copy_pu8State);

#endif

/*
PORTA				DIO_u8PORTA         0u
PORTB				DIO_u8PORTB         1u
PORTC				DIO_u8PORTC         2u
PORTD				DIO_u8PORTD         3u

PIN0				DIO_u8PIN0          0u
PIN1				DIO_u8PIN1          1u
PIN2				DIO_u8PIN2          2u
PIN3				DIO_u8PIN3          3u
PIN4				DIO_u8PIN4          4u
PIN5				DIO_u8PIN5          5u
PIN6				DIO_u8PIN6          6u
PIN7				DIO_u8PIN7          7u

PORT INPUT			DIO_u8PORT_INPUT    0
PORT OUTPUT			DIO_u8PORT_OUTPUT   0xff

PORT LOW			DIO_u8PORT_LOW      0
PORT HIGH			DIO_u8PORT_HIGH     0xff

PIN INPUT			DIO_u8PIN_INPUT     0u
PIN OUTPUT			DIO_u8PIN_OUTPUT    1u

PIN LOW 			DIO_u8PIN_LOW       0u
PIN HIGH 			DIO_u8PIN_HIGH      1u
*/
