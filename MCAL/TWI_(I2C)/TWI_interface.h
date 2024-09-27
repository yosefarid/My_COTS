#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

typedef enum {
    NoError,
    NULLPtrErr,
	MasterInit,
	SlaveInit,
    StartCondErr,
    RepStartErr,
    SlaveAddressWithWriteErr,
    SlaveAddressWithReadErr,
    MstrWriteByteWithACKErr,
	MstrReadByteWithACKErr
	
} TWI_ErrorStatus_t;

/*if Master is not addressed in the network pass address 0*/
TWI_ErrorStatus_t TWI_voidMasterInit(uint8 Copy_u8Address);
TWI_ErrorStatus_t TWI_voidSlaveInit(uint8 Copy_u8Address);
TWI_ErrorStatus_t TWI_voidSendStartCondition(void);
TWI_ErrorStatus_t TWI_voidSendRepeatedStartCondition(void);
TWI_ErrorStatus_t TWI_voidSendSlaveAddWrite(uint8 Copy_u8SLA);
TWI_ErrorStatus_t TWI_voidSendSlaveAddRead(uint8 Copy_u8SLA);
TWI_ErrorStatus_t TWI_voidMasterWriteDataByte(uint8 Copy_u8DataByte);
TWI_ErrorStatus_t TWI_voidMasterReadDataByte(uint8* Copy_pu8DataByte);

void TWI_voidSendStopCondition(void);

#endif
