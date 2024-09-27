#ifndef SPI_REGISTER_H
#define SPI_REGISTER_H

#define SPCR					*((volatile uint8*)0x2D)		/*SPI Control Register*/
#define SPCR_SPIE				7u                              /*SPI Interrupt Enable*/
#define SPCR_SPE				6u                              /*SPI Enable*/
#define SPCR_DORD				5u                              /*Data Order*/
#define SPCR_MSTR				4u                              /*Master/Slave Select*/
#define SPCR_CPOL				3u                              /*Clock Polarity*/
#define SPCR_CPHA				2u                              /*Clock Phase*/

#define SPSR					*((volatile uint8*)0x2E)		/*SPI Status Register*/
#define SPSR_SPIF				7u 								/*SPI Interrupt Flag*/
#define SPSR_WCOL				6u                              /*Write COLlision Flag*/
#define SPSR_SPI2X				0u                              /*Double SPI Speed Bit*/

#define SPDR					*((volatile uint8*)0x2F)		/*SPI Data Register*/

#endif