#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

#include "DIO_interface.h"

typedef struct
{
	uint8 SSD_u8ComType;
	uint8 SSD_u8Port;
	uint8 SSD_u8Enable_Port;
	uint8 SSD_u8Enable_Pin;
}SSD_t;

#define SSD_u8External 			9u
//case of using external Vcc or Ground set SSD_u8Enable_Port & SSD_u8Enable_Pin with SSD_u8External

#define SSD_u8_zero				0u
#define SSD_u8_one				1u
#define SSD_u8_two				2u
#define SSD_u8_three			3u
#define SSD_u8_four				4u
#define SSD_u8_five				5u
#define SSD_u8_six				6u
#define SSD_u8_seven			7u
#define SSD_u8_eight			8u
#define SSD_u8_nine				9u

#define Com_Cathode 			0u
#define Com_Anode 				1u

uint8 SSD_u8SetNumber(uint8 Copy_u8Number , SSD_t * Copy_pssdComponent);
uint8 SSD_u8Enable(SSD_t * Copy_pssdComponent);
uint8 SSD_u8Disable(SSD_t * Copy_pssdComponent);


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
