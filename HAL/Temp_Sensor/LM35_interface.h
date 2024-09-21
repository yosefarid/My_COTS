#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H

typedef struct
{
	uint8 Vref;
	uint8 resolution;
}ADC_info;

#define RES_EIGHT_BITS				8
#define RES_TEN_BITS				10

#define Vref_AVCC					5
#define Vref_INTERNAL				2.56


uint8 LM35_getTemperature(ADC_info* Copy_component , uint16 Copy_u16DigTemp , uint16* Copy_pu16Result);


#endif