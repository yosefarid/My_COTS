#ifndef CLCD_CONFIG_H
#define CLCD_CONFIG_H

/*configure the LCD BIT MODE, The options are:		1- FOUR_BIT
 * 													2- EIGHT_BIT*/

#define CLCD_u8BIT_MODE				FOUR_BIT

#define CLCD_u8CTRL_Port			DIO_u8PORTC

#define CLCD_u8RS_PIN				DIO_u8PIN0
#define CLCD_u8RW_PIN				DIO_u8PIN1
#define CLCD_u8E_PIN				DIO_u8PIN2

#define CLCD_u8Data_Port			DIO_u8PORTC

#if CLCD_u8BIT_MODE == FOUR_BIT
#define CLCD_u8D4_Pin				DIO_u8PIN3
#define CLCD_u8D5_Pin				DIO_u8PIN4
#define CLCD_u8D6_Pin				DIO_u8PIN5
#define CLCD_u8D7_Pin				DIO_u8PIN6
#endif

#endif
