#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "DIO_interface.h"
#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"

uint8 SW_u8GetState(SW_t * Copy_pswComponent , uint8 * Copy_pu8State)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pswComponent != NULL)
	{
		if(Copy_pswComponent -> SW_u8PullType == SW_u8PullUp)
		{
			uint8 Local_u8ErrPullUp1 = DIO_u8SetPinDirection(Copy_pswComponent -> SW_u8Port , Copy_pswComponent -> SW_u8Pin , DIO_u8PIN_INPUT);
			uint8 Local_u8ErrPullUp2 = DIO_u8SetPinValue(Copy_pswComponent -> SW_u8Port , Copy_pswComponent -> SW_u8Pin , DIO_u8PIN_HIGH);
			uint8 Local_u8ErrPullUp3 = DIO_u8ReadPinValue(Copy_pswComponent -> SW_u8Port , Copy_pswComponent -> SW_u8Pin , Copy_pu8State);

			if(Local_u8ErrPullUp1 == NOK || Local_u8ErrPullUp2 == NOK || Local_u8ErrPullUp3 == NOK)
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if(Copy_pswComponent -> SW_u8PullType == SW_u8PullDown)
		{
			uint8 Local_u8ErrPullDown1 = DIO_u8SetPinDirection(Copy_pswComponent -> SW_u8Port , Copy_pswComponent -> SW_u8Pin , DIO_u8PIN_INPUT);
			uint8 Local_u8ErrPullDown2 = DIO_u8ReadPinValue(Copy_pswComponent -> SW_u8Port , Copy_pswComponent -> SW_u8Pin , Copy_pu8State);

			if(Local_u8ErrPullDown1 == NOK || Local_u8ErrPullDown2 == NOK)
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
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}
