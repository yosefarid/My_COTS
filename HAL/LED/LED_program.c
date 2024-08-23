#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

uint8 LED_u8TurnOn(LED_t * Copy_pledComponent)//+
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pledComponent == NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	else
	{
		if(Copy_pledComponent -> LED_u8ConnType == LED_u8Source)
		{
			uint8 Local_u8ErrSource1 = DIO_u8SetPinDirection(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrSource2 = DIO_u8SetPinValue(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_HIGH);

			if(Local_u8ErrSource1 == NOK || Local_u8ErrSource2 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if(Copy_pledComponent -> LED_u8ConnType == LED_u8Sink)
		{
			uint8 Local_u8ErrSink1 = DIO_u8SetPinDirection(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrSink2 = DIO_u8SetPinValue(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_LOW);

			if(Local_u8ErrSink1 == NOK || Local_u8ErrSink2 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}

	return Local_u8ErrorState;
}

uint8 LED_u8TurnOff(LED_t * Copy_pledComponent)//+
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pledComponent == NULL)
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	else
	{
		if(Copy_pledComponent -> LED_u8ConnType == LED_u8Source)
		{
			uint8 Local_u8ErrSource3 = DIO_u8SetPinDirection(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrSource4 = DIO_u8SetPinValue(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_LOW);

			if(Local_u8ErrSource3 == NOK || Local_u8ErrSource3 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if(Copy_pledComponent -> LED_u8ConnType == LED_u8Sink)
		{
			uint8 Local_u8ErrSink3 = DIO_u8SetPinDirection(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_OUTPUT);
			uint8 Local_u8ErrSink4 = DIO_u8SetPinValue(Copy_pledComponent -> LED_u8Port , Copy_pledComponent -> LED_u8Pin , DIO_u8PIN_HIGH);

			if(Local_u8ErrSink3 == NOK || Local_u8ErrSink4 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}

	return Local_u8ErrorState;
}
