#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "TWI_register.h"
#include "TWI_private.h"
#include "TWI_config.h"
#include "TWI_interface.h"

/*if Master is not addressed in the network pass address 0*/
TWI_ErrorStatus_t TWI_voidMasterInit(uint8 Copy_u8Address)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	if(Copy_u8Address != 0u)
	{
		if((Copy_u8Address >> 3) == 0b1111)
		{
			/*Error "Reserved address"*/
			Local_u8ErrState = MasterInit;
		}
		else
		{
			/*Master will be addressed in the network, assign the address*/
			TWAR = Copy_u8Address << 1;
		}
	}

	/*CPU freq = 16000000 , prescaler = 0 , communication freq = 400kbps*/
	CLR_BIT(TWSR , TWSR_TWPS0);
	CLR_BIT(TWSR , TWSR_TWPS1);
	TWBR = 12;

	/*Enable acknowledge*/
	SET_BIT(TWCR , TWCR_TWEA);

	/*TWI Enable*/
	SET_BIT(TWCR , TWCR_TWEN);

	return Local_u8ErrState;
}

TWI_ErrorStatus_t TWI_voidSlaveInit(uint8 Copy_u8Address)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	if(Copy_u8Address != 0u)
	{
		if((Copy_u8Address >> 3) == 0b1111)
		{
			/*Error "Reserved address"*/
			Local_u8ErrState = MasterInit;
		}
		else
		{
			/*Master will be addressed in the network, assign the address*/
			TWAR = Copy_u8Address << 1;
		}
	}

	/*TWI Enable*/
	SET_BIT(TWCR , TWCR_TWEN);

	return Local_u8ErrState;
}

TWI_ErrorStatus_t TWI_voidSendStartCondition(void)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	/*Set start condition bit*/
	SET_BIT(TWCR , TWCR_TWSTA);

	/*Clear interrupt flag to enable previous operation to happen*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*wait until the previous operation finishes and the interrupt flag is raised*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != START_ACK)
	{
		Local_u8ErrState = StartCondErr;
	}
	else
	{
		/*do nothing*/
	}

	return Local_u8ErrState;
}

TWI_ErrorStatus_t TWI_voidSendRepeatedStartCondition(void)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	/*Set start condition bit*/
	SET_BIT(TWCR , TWCR_TWSTA);

	/*Clear interrupt flag to enable previous operation to happen*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*wait until the previous operation finishes and the interrupt flag is raised*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != REP_START_ACK)
	{
		Local_u8ErrState = RepStartErr;
	}
	else
	{
		/*do nothing*/
	}

	return Local_u8ErrState;
}

TWI_ErrorStatus_t TWI_voidSendSlaveAddWrite(uint8 Copy_u8SLA)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	/*Set slave address into the data register*/
	TWDR = Copy_u8SLA << 1u;

	/*Clear bit 0 for write request*/
	CLR_BIT(TWDR , 0u);

	/*Clear start condition bit*/
	SET_BIT(TWCR , TWCR_TWSTA);

	/*Clear interrupt flag to enable previous operation to happen*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*wait until the previous operation finishes and the interrupt flag is raised*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_u8ErrState = SlaveAddressWithWriteErr;
	}
	else
	{
		/*do nothing*/
	}

	return Local_u8ErrState;
}

TWI_ErrorStatus_t TWI_voidSendSlaveAddRead(uint8 Copy_u8SLA)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	/*Set slave address into the data register*/
	TWDR = Copy_u8SLA << 1u;

	/*Set bit 0 for Read request*/
	SET_BIT(TWDR , 0u);

	/*Clear start condition bit*/
	SET_BIT(TWCR , TWCR_TWSTA);

	/*Clear interrupt flag to enable previous operation to happen*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*wait until the previous operation finishes and the interrupt flag is raised*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_u8ErrState = SlaveAddressWithReadErr;
	}
	else
	{
		/*do nothing*/
	}

	return Local_u8ErrState;
}

TWI_ErrorStatus_t TWI_voidMasterWriteDataByte(uint8 Copy_u8DataByte)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	/*put the data into the data register to be sent on the bus*/
	TWDR = Copy_u8DataByte;

	/*Clear interrupt flag to enable previous operation to happen*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*wait until the previous operation finishes and the interrupt flag is raised*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

	/*Check the status of the bus*/
	if((TWSR & STATUS_BITS_MASK) != MSTR_WR_BYTE_WITH_ACK)
	{
		Local_u8ErrState = MstrWriteByteWithACKErr;
	}
	else
	{
		/*do nothing*/
	}

	return Local_u8ErrState;
}

TWI_ErrorStatus_t TWI_voidMasterReadDataByte(uint8* Copy_pu8DataByte)
{
	TWI_ErrorStatus_t Local_u8ErrState = NoError;

	if(Copy_pu8DataByte != NULL)
	{
		/*Clear interrupt flag to enable slave to send data*/
		SET_BIT(TWCR , TWCR_TWINT);

		/*wait until the previous operation finishes and the interrupt flag is raised*/
		while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

		/*Check the status of the bus*/
		if((TWSR & STATUS_BITS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_u8ErrState = MstrReadByteWithACKErr;
		}
		else
		{
			*Copy_pu8DataByte = TWDR;
		}
	}
	else
	{
		Local_u8ErrState = NULLPtrErr;
	}

	return Local_u8ErrState;
}

void TWI_voidSendStopCondition(void)
{
	/*Set stop condition bit*/
	SET_BIT(TWCR , TWCR_TWSTO);

	/*Clear interrupt flag to enable slave to send data*/
	SET_BIT(TWCR , TWCR_TWINT);
}
