#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "DIO_interface.h"
#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"


uint8 SSD_u8SetNumber(uint8 Copy_u8Number , SSD_t * Copy_pssdComponent)//+
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pssdComponent != NULL)
	{

		if(Copy_u8Number >= SSD_u8_zero && Copy_u8Number <= SSD_u8_nine)
		{

			if(Copy_pssdComponent -> SSD_u8ComType == Com_Cathode)
			{

				uint8 Local_u8ErrCount_Com_Cathode1 = DIO_u8SetPortDirection(Copy_pssdComponent -> SSD_u8Port , DIO_u8PORT_OUTPUT);
				uint8 Local_u8ErrCount_Com_Cathode2 = DIO_u8SetPortValue(Copy_pssdComponent -> SSD_u8Port , SSD_u8NumArr[Copy_u8Number]);

				if(Local_u8ErrCount_Com_Cathode1 == NOK || Local_u8ErrCount_Com_Cathode2 == NOK)
				{
					Local_u8ErrorState = NOK;
				}

				if(Copy_pssdComponent -> SSD_u8Enable_Port != SSD_u8External || Copy_pssdComponent -> SSD_u8Enable_Pin != SSD_u8External)
				{
					if(GET_BIT(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin) != DIO_u8PIN_LOW )
					{
						Local_u8ErrorState = NOK;
					}
				}

			}
			else if(Copy_pssdComponent -> SSD_u8ComType == Com_Anode)
			{

				uint8 Local_u8ErrCount_Com_Anode1 = DIO_u8SetPortDirection(Copy_pssdComponent -> SSD_u8Port , DIO_u8PORT_OUTPUT);
				uint8 Local_u8ErrCount_Com_Anode2 = DIO_u8SetPortValue(Copy_pssdComponent -> SSD_u8Port , ~SSD_u8NumArr[Copy_u8Number]);

				if(Local_u8ErrCount_Com_Anode1 == NOK || Local_u8ErrCount_Com_Anode2 == NOK)
				{
					Local_u8ErrorState = NOK;
				}

				if(Copy_pssdComponent -> SSD_u8Enable_Port != SSD_u8External || Copy_pssdComponent -> SSD_u8Enable_Pin != SSD_u8External)
				{
					if(GET_BIT(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin) != DIO_u8PIN_HIGH )
					{
						Local_u8ErrorState = NOK;
					}
				}

			}
			else
			{
				Local_u8ErrorState = NOK;
			}

		}
		else
		{
			Local_u8ErrorState = NOK;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 SSD_u8Enable(SSD_t * Copy_pssdComponent)//+
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pssdComponent != NULL)
	{
		if(Copy_pssdComponent -> SSD_u8ComType == Com_Cathode)
		{
			uint8 Local_u8ErrCount_Com_Cathode3 = DIO_u8SetPinDirection(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrCount_Com_Cathode4 = DIO_u8SetPinValue(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_LOW);

			if(Local_u8ErrCount_Com_Cathode3 == NOK || Local_u8ErrCount_Com_Cathode4 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if(Copy_pssdComponent -> SSD_u8ComType == Com_Anode)
		{
			uint8 Local_u8ErrCount_Com_Anode3 = DIO_u8SetPinDirection(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrCount_Com_Anode4 = DIO_u8SetPinValue(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_HIGH);

			if(Local_u8ErrCount_Com_Anode3 == NOK || Local_u8ErrCount_Com_Anode4 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 SSD_u8Disable(SSD_t * Copy_pssdComponent)//+
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pssdComponent != NULL)
	{
		if(Copy_pssdComponent -> SSD_u8ComType == Com_Cathode)
		{
			uint8 Local_u8ErrCount_Com_Cathode5 = DIO_u8SetPinDirection(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrCount_Com_Cathode6 = DIO_u8SetPinValue(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_HIGH);

			if(Local_u8ErrCount_Com_Cathode5 == NOK || Local_u8ErrCount_Com_Cathode6 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if(Copy_pssdComponent -> SSD_u8ComType == Com_Anode)
		{
			uint8 Local_u8ErrCount_Com_Anode5 = DIO_u8SetPinDirection(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrCount_Com_Anode6 = DIO_u8SetPinValue(Copy_pssdComponent -> SSD_u8Enable_Port , Copy_pssdComponent -> SSD_u8Enable_Pin , DIO_u8PIN_LOW);

			if(Local_u8ErrCount_Com_Anode5 == NOK || Local_u8ErrCount_Com_Anode6 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
