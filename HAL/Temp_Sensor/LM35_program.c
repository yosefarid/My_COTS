#include "STD_types.h"

#include "LM35_interface.h"
#include "ADC_interface.h"

uint8 LM35_getTemperature(ADC_info* Copy_component , uint16 Copy_u16DigTemp , uint16* Copy_pu16Result)
{
	u8 Local_u8ErrState = OK;
	
	if(Copy_component != NULL)
	{

		if(Copy_component -> resolution == 8)
		{
			Dig_Temp = (uint16) Map(0 , 5 , 0 , Copy_component -> Vref ,Dig_Temp);
			*Result  = (uint16)( ((uint32)Dig_Temp * ((uint32)(Copy_component -> Vref) * 100UL) ) / 255UL);
		}
		else if(Copy_component -> resolution == 10)
		{
			Dig_Temp = (uint16) Map(0 , 5 , 0 , Copy_component -> Vref ,Dig_Temp);
			Dig_Temp = (uint16) Map(0 , 1023 , 0 , 255 ,Dig_Temp);
			*Result = (uint16)(((uint32)Dig_Temp * ((uint32)(Copy_component -> Vref) * 100UL) ) / 1023UL);
		}
		else
		{
			Local_u8ErrState = NOK;
		}
	}
	else
	{
		Local_u8ErrState = NULL_PTR_ERR;
	}
	
	return Local_u8ErrState;
}