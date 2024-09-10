#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/*configure the voltage reference options for ADC, Options:
 * 															1- AREF     	//put your reference voltage on AREF pin
 * 															2- AVCC			//voltage reference 5V
 * 															3- INTERNAL		//internal voltage reference 2.56V
 * 	*/
#define ADC_u8Voltage_Ref						AVCC

/*configure the Resolution options for ADC, Options:
 * 															1- _8_BIT
 * 															2- _10_BIT
 * 	*/
#define ADC_u8Resolution						_8_BIT

/*configure the Conversion mode options for ADC, Options:
 * 															1- Manual
 * 															2- Auto_Trigger
 * 	*/
#define ADC_u8Conv_Mode							Manual

/*configure the ADC Interrupt State, Options:
 * 															1- ON
 * 															2- OFF
 * 	*/
#define ADC_u8Interrupt							OFF

/*configure the ADC Interrupt State, Options:
 * 															1- Division_by_2
 * 															2- Division_by_4
 * 															3- Division_by_8
 * 															4- Division_by_16
 * 															5- Division_by_32
 * 															6- Division_by_64
 * 															7- Division_by_128
 * 	*/
#define ADC_u8PrescalerDivisionFactor			Division_by_128

#if ADC_u8Conv_Mode == Auto_Trigger

/*configure the ADC Trigger Source, Options:
 * 														1- Free_Running_mode
 * 														2- Analog_Comparator
 * 														3- External_Interrupt_Request_0
 * 														4- Counter0_Compare_Match
 * 														5- Counter0_Overflow
 * 														6- Counter_Compare_Match B
 * 														7- Counter1_Overflow
 * 														8- Counter1_Capture_Event
 * 	*/
#define ADC_u8TriggerSource						Free_Running_mode

#endif

#endif
