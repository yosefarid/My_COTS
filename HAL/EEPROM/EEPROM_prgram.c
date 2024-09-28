#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void EEPROM_voidWriteDataByte(uint16 Copy_u16LocAddress , uint8 Copy_u8DataByte)
{
	/*Get the 7 bit slave address*/
	uint8 Local_u8SlaveAddress = EEPROM_FIXED_ADRESS | (A2_connection << 2u) | ((Copy_u16LocAddress >> 8) & 0x3);

	/*Send start condition*/
	TWI_voidSendStartCondition();

	/*Send the 7bit SLA with write request*/
	TWI_voidSendSlaveAddWrite(Local_u8SlaveAddress);

	/*Send the rest 8 bits of the location address*/
	TWI_voidMasterWriteDataByte((uint8) Copy_u16LocAddress);

	/*Send the data to be written inside the memory location*/
	TWI_voidMasterWriteDataByte(Copy_u8DataByte);

	/*Send the stop condition*/
	TWI_voidSendStopCondition();

	/*wait until write cycle is finished*/
	_delay_ms(10);
}

uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocAddress)
{
	uint8 Local_u8LocationData;

	/*Get the 7 bit slave address*/
	uint8 Local_u8SlaveAddress = EEPROM_FIXED_ADRESS | (A2_connection << 2u) | ((Copy_u16LocAddress >> 8) & 0x3);

	/*Send start condition*/
	TWI_voidSendStartCondition();

	/*Send the 7bit SLA with write request*/
	TWI_voidSendSlaveAddWrite(Local_u8SlaveAddress);

	/*Send the rest 8 bits of the location address*/
	TWI_voidMasterWriteDataByte((uint8) Copy_u16LocAddress);

	/*Send repeated start to change from write to read*/
	TWI_voidSendRepeatedStartCondition();

	/*Send the 7bit SLA with Read request*/
	TWI_voidSendSlaveAddRead(Local_u8SlaveAddress);

	/*Read from eeprom*/
	TWI_voidMasterReadDataByte(&Local_u8LocationData);
	
	/*Send the stop condition*/
	TWI_voidSendStopCondition();

	return Local_u8LocationData;
}
