#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "DIO_interface.h"
#include "Motor_interface.h"
#include "Motor_private.h"
#include "Motor_config.h"


uint8 Motor_u8RotateCW(Motor_t * Copy_pmotorComponent)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_pmotorComponent != NULL)
	{
		DIO_u8SetPinValue(Copy_pmotorComponent->Motor_u8ConnPort , Copy_pmotorComponent->Motor_u8ConnPin1 , DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pmotorComponent->Motor_u8ConnPort , Copy_pmotorComponent->Motor_u8ConnPin2 , DIO_u8PIN_LOW);
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

uint8 Motor_u8RotateCCW(Motor_t * Copy_pmotorComponent)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_pmotorComponent != NULL)
	{
		DIO_u8SetPinValue(Copy_pmotorComponent->Motor_u8ConnPort , Copy_pmotorComponent->Motor_u8ConnPin1 , DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pmotorComponent->Motor_u8ConnPort , Copy_pmotorComponent->Motor_u8ConnPin2 , DIO_u8PIN_HIGH);
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}

uint8 Motor_u8Stop(Motor_t * Copy_pmotorComponent)
{
	uint8 Local_u8ErrState = OK;

	if(Copy_pmotorComponent != NULL)
	{
		DIO_u8SetPinValue(Copy_pmotorComponent->Motor_u8ConnPort , Copy_pmotorComponent->Motor_u8ConnPin1 , DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Copy_pmotorComponent->Motor_u8ConnPort , Copy_pmotorComponent->Motor_u8ConnPin2 , DIO_u8PIN_HIGH);
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}

	return Local_u8ErrState;
}
