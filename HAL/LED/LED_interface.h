#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "DIO_interface.h"

typedef struct
{
	uint8 LED_u8ConnType;
	uint8 LED_u8Port;
	uint8 LED_u8Pin;
}LED_t;

#define LED_u8Source	0u
#define LED_u8Sink		1u

uint8 LED_u8TurnOn(LED_t * Copy_pledComponent);
uint8 LED_u8TurnOff(LED_t * Copy_pledComponent);

// turn on the whole port and off is missing
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
