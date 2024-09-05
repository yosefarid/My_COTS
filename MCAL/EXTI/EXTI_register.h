#ifndef EXTI_REGISTER_H
#define EXTI_REGISTER_H

#define GICR				*((volatile uint8*)0x5B) /*General Interrupt Control Register*/
#define GICR_INT0			6u                       /*INT0 BIT*/
#define GICR_INT1			7u                       /*INT1 BIT*/
#define GICR_INT2			5u                       /*INT2 BIT*/

#define GIFR				*((volatile uint8*)0x5A) /*General Interrupt Flag Register*/
#define GIFR_INTF0			6u                       /*INTF0 BIT*/
#define GIFR_INTF1			7u                       /*INTF1 BIT*/
#define GIFR_INTF2			5u                       /*INTF2 BIT*/

#define MCUCR				*((volatile uint8*)0x55) /*MCU Control Register*/
#define MCUCR_ISC00			0u                       /*INT0 Sense Control Bit 0*/
#define MCUCR_ISC01			1u                       /*INT0 Sense Control Bit 1*/
#define MCUCR_ISC10			2u                       /*INT1 Sense Control Bit 0*/
#define MCUCR_ISC11			3u                       /*INT1 Sense Control Bit 1*/

#define MCUCSR				*((volatile uint8*)0x54) /*MCU Control and Status Register*/
#define MCUCSR_ISC2			6u                       /*INT2 Sense Control Bit*/

#endif
