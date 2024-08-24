#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

#if CLCD_u8BIT_MODE == FOUR_BIT
static void SetHalfDataPort(uint8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_u8Data_Port , CLCD_u8D4_Pin , GET_BIT(Copy_u8Data , 0));
	DIO_u8SetPinValue(CLCD_u8Data_Port , CLCD_u8D5_Pin , GET_BIT(Copy_u8Data , 1));
	DIO_u8SetPinValue(CLCD_u8Data_Port , CLCD_u8D6_Pin , GET_BIT(Copy_u8Data , 2));
	DIO_u8SetPinValue(CLCD_u8Data_Port , CLCD_u8D7_Pin , GET_BIT(Copy_u8Data , 3));
}
#endif

static void voidSendEnablePulse(void)
{
	/*send enable pulse*/
	DIO_u8SetPinValue(CLCD_u8CTRL_Port , CLCD_u8E_PIN , DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_Port , CLCD_u8E_PIN , DIO_u8PIN_LOW);
}

void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{
	/*set RS low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_Port , CLCD_u8RS_PIN , DIO_u8PIN_LOW);
	/*set RW low for write */
	DIO_u8SetPinValue(CLCD_u8CTRL_Port , CLCD_u8RW_PIN , DIO_u8PIN_LOW);

#if CLCD_u8BIT_MODE == EIGHT_BIT
	/*send the command*/
	DIO_u8SetPortValue(CLCD_u8Data_Port , Copy_u8Cmd);
	voidSendEnablePulse();
#elif CLCD_u8BIT_MODE == FOUR_BIT
	/*Send the most significant bits of the command first*/
	SetHalfDataPort(Copy_u8Cmd >> 4);
	voidSendEnablePulse();
	SetHalfDataPort(Copy_u8Cmd);
	voidSendEnablePulse();
#else
	#error wrong CLCD_u8BIT_MODE configration option
#endif

}

void CLCD_voidSendData(uint8 Copy_u8Data)
{
	/*set RS low for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_Port , CLCD_u8RS_PIN , DIO_u8PIN_HIGH);
	/*set RW low for write */
	DIO_u8SetPinValue(CLCD_u8CTRL_Port , CLCD_u8RW_PIN , DIO_u8PIN_LOW);

#if CLCD_u8BIT_MODE == EIGHT_BIT
	/*send the Data*/
	DIO_u8SetPortValue(CLCD_u8Data_Port , Copy_u8Data);
	voidSendEnablePulse();
#elif CLCD_u8BIT_MODE == FOUR_BIT
	/*Send the most significant bits of the data first*/
	SetHalfDataPort(Copy_u8Data >> 4);
	voidSendEnablePulse();
	SetHalfDataPort(Copy_u8Data);
	voidSendEnablePulse();
#else
	#error wrong CLCD_u8BIT_MODE configration option
#endif

}

void CLCD_voidInit(void)
{
	/*wait for more than 30ms for power on*/
	_delay_ms(40);

	/*function set command: 2lines , font size: 5x7*/
#if CLCD_u8BIT_MODE == EIGHT_BIT

	CLCD_voidSendCmd(0b00111000);

#elif CLCD_u8BIT_MODE == FOUR_BIT

	SetHalfDataPort(0b0010);
	voidSendEnablePulse();
	SetHalfDataPort(0b0010);
	voidSendEnablePulse();
	SetHalfDataPort(0b1000);
	voidSendEnablePulse();

#endif
	/*display on off control: display on , cursor off , blink cursor off*/
	CLCD_voidSendCmd(0b00001100);
	/*clear display*/
	CLCD_voidSendCmd(1);
}

uint8 CLCD_u8SendString(const char * Copy_pchString)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_pchString != NULL)
	{
		while(*Copy_pchString != '\0')
		{
			CLCD_voidSendData(*Copy_pchString);
			Copy_pchString ++;
		}
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

void CLCD_voidSendNumber(sint32 Copy_s32Number)
{
	if(Copy_s32Number == 0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else if(Copy_s32Number < 0)
	{
		Copy_s32Number *= -1;
		CLCD_voidSendData('-');
	}

		uint8 Local_u8Counter = 0;
		sint32 Local_s32NumArr[Max_num_numbers];

		while(Copy_s32Number != 0)
		{
			Local_s32NumArr[Local_u8Counter] = Copy_s32Number % decimal_base;
			Copy_s32Number /= decimal_base;
			Local_u8Counter ++;
		}
		Local_u8Counter --;
		for(uint8 Local_u8counter2 = Local_u8Counter ; Local_u8counter2 >= 0 ; Local_u8counter2 --)
		{

			CLCD_voidSendData('0' + Local_s32NumArr[Local_u8counter2]);

			if(Local_u8counter2 == 0)
			{
				break;
			}
		}
}

void CLCD_voidGoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8Address ;
	if(Copy_u8YPos == 0u)
	{
		Local_u8Address = Copy_u8XPos;
	}
	else if(Copy_u8YPos == 1u)
	{
		Local_u8Address = 0x40 + Copy_u8XPos;
	}
	// Local_u8Address = 0x40 * Copy_u8YPos + Copy_u8XPos;

	/*Set bit 7 for SetDDRAM Address command*/
	SET_BIT(Local_u8Address,7);

	/*Execute Set DDRAM Address command*/
	CLCD_voidSendCmd(Local_u8Address);
}

uint8 CLCD_u8SendSpecialCharacter(uint8 Copy_u8LocationNum , uint8 * Copy_pu8Pattern , uint8  Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_pu8Pattern != NULL)
	{
		uint8 Local_u8Counter;

		uint8 Local_u8CGRAMAddress = Copy_u8LocationNum * 8;
		/*Set bit 6 for CGRAM address command*/
		SET_BIT(Local_u8CGRAMAddress , 6u);
		/*Set CGRAM address*/
		CLCD_voidSendCmd(Local_u8CGRAMAddress);
		/*Write the input pattern inside CGRAM*/
		for(Local_u8Counter = zero ; Local_u8Counter < Byte_Size ; Local_u8Counter ++)
		{
			CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
		}
		/*Go back to DDRAM*/
		CLCD_voidGoToXY(Copy_u8XPos , Copy_u8YPos);
		/*Write the special character inside CGRAM*/
		CLCD_voidSendData(Copy_u8LocationNum);

	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}
