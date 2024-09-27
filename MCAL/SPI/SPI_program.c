#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_register.h"
#include "SPI_config.h"
#include "SPI_private.h"
#include "SPI_interface.h"

void SPI_voidInit(void)
{
	/*Set data order*/
	CLR_BIT(SPCR , SPCR_DORD);

	/*Choose clock configuration*/
	CLR_BIT(SPCR , SPCR_CPOL);
	CLR_BIT(SPCR , SPCR_CPHA);

	/*Select SPI clock rate*/
	SET_BIT(SPCR , 0);
	SET_BIT(SPCR , 1);
	CLR_BIT(SPSR, SPSR_SPI2X);

	/*Choose mode Master*/
	SET_BIT(SPCR , SPCR_MSTR);

	/*Enable the SPI*/
	SET_BIT(SPCR , SPCR_SPE);
}

uint8 SPI_u8Transceive(uint8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
	while(GET_BIT(SPSR , SPSR_SPIF) == 0);
	return SPDR;
}
