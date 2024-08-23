#include "STD_TYPES.h"
#include "ErrType.h"

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

uint8 KPD_u8GetPressedKey(void)
{
	uint8 Local_u8ColIdx , Local_u8RowIdx , Local_u8PinState , Local_u8PressedKey = KPD_No_Pressed_Key_Val;

	uint8 Local_au8ColArr[Col_Num] = {KPD_U8COL0_PIN , KPD_U8COL1_PIN , KPD_U8COL2_PIN , KPD_U8COL3_PIN};

	uint8 Local_au8RowArr[Row_Num] = {KPD_U8ROW0_PIN , KPD_U8ROW1_PIN , KPD_U8ROW2_PIN , KPD_U8ROW3_PIN};

	uint8 Local_au8KPDArr[Row_Num][Col_Num] = KPD_au8Button_Arr;

	/*Activate the columns pins*/
	for(Local_u8ColIdx = Zero ; Local_u8ColIdx < Col_Num ; Local_u8ColIdx ++)
	{
		/*Activate the current column*/
		DIO_u8SetPinValue(KPD_u8COL_PORT , Local_au8ColArr[Local_u8ColIdx] , DIO_u8PIN_LOW);

		/*Read the row pins*/
		for(Local_u8RowIdx = Zero ; Local_u8RowIdx < Row_Num ; Local_u8RowIdx ++)
		{
			/*Read the current row*/
			DIO_u8ReadPinValue(KPD_u8ROW_PORT , Local_au8RowArr[Local_u8RowIdx] , &Local_u8PinState);

			if(Local_u8PinState == DIO_u8PIN_LOW)
			{
				Local_u8PressedKey = Local_au8KPDArr[Local_u8RowIdx][Local_u8ColIdx];

				/*Polling with blocking(waiting) until the key is released*/
				while(Local_u8PinState == DIO_u8PIN_LOW)
				{
					DIO_u8ReadPinValue(KPD_u8ROW_PORT , Local_au8RowArr[Local_u8RowIdx] , &Local_u8PinState);
				}

				return Local_u8PressedKey;
			}
		}

		/*Deactivate the current column*/
		DIO_u8SetPinValue(KPD_u8COL_PORT , Local_au8ColArr[Local_u8ColIdx] , DIO_u8PIN_HIGH);
	}

	return Local_u8PressedKey;
}
