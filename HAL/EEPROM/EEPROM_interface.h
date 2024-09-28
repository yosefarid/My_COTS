#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

void EEPROM_voidWriteDataByte(uint16 Copy_u16LocAddress , uint8 Copy_u8DataByte);

uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocAddress);

#endif