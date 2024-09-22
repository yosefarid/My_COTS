#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#define TIMER0_OVF_INT			0u
#define TIMER0_OC_INT			1u
#define TIMER1_OVF_INT			2u
#define TIMER1_B_OC_INT			3u
#define TIMER1_A_OC_INT			4u
#define TIMER1_ICU_INT			5u
#define TIMER2_OVF_INT			6u
#define TIMER2_OC_INT			7u

#define	Falling_edge			0u
#define rising_edge				1u

typedef enum
{
	Normal,
	PWM_Phase_Correct,
	CTC,
	Fast_PWM
}WGM_t;

typedef enum
{
	Normal_COM,
	Toggle,
	Clear,
	Set
}COM_CTC_t;

typedef enum
{
	Clear_On_Compare = 2,
	Set_On_Compare
}COM_PWM_t;

typedef enum
{
	NO_DIV = 1,
	DIV_BY_8,
	DIV_BY_64,
	DIV_BY_256,
	DIV_BY_1024,
	EXT_Clock_Falling_Edge,
	EXT_Clock_Rising_Edge
}Prescaler_t;

typedef enum
{
	NO_DIV_2 = 1,
	DIV_BY_8_2,
	DIV_BY_32,
	DIV_BY_64_2,
	DIV_BY_128,
	DIV_BY_256_2,
	DIV_BY_1024_2
}Prescale_2_t;

typedef struct
{
	WGM_t Wave_mode;
	COM_CTC_t Compare_Mode;
	COM_PWM_t Compare_PWM_Mode;
	Prescaler_t Prescaler;
	Prescale_2_t Prescaler_2;
}TIM_0_2_t;

typedef enum
{
	Channel_A,
	Channel_B
}Channel_t;

typedef enum
{
	NORMAL,
	PWM_Phase_Correct_8bit,
	PWM_Phase_Correct_9bit,
	PWM_Phase_Correct_10bit,
	CTC_OCR,
	Fast_PWM_8bit,
	Fast_PWM_9bit,
	Fast_PWM_10bit,
	PWM_Phase_Frequency_Correct_ICR,
	PWM_Phase_Frequency_Correct_OCR,
	PWM_Phase_Correct_ICR,
	PWM_Phase_Correct_OCR,
	CTC_ICR,
	Fast_PWM_ICR = 14,
	Fast_PWM_OCR
}WGM_TIM1_t;

typedef struct
{
	WGM_TIM1_t Wave_mode;
	Channel_t Channel;
	COM_CTC_t Compare_Mode;
	COM_PWM_t Compare_PWM_Mode;
	Prescaler_t Prescaler;
}TIM_1_t;


uint8 TIMER0_u8Init(TIM_0_2_t* Copy_Configuration);

uint8 TIMER1_u8Init(TIM_1_t* Copy_Configuration);

uint8 TIMER2_u8Init(TIM_0_2_t* Copy_Configuration);

void TIMER0_voidSetPreloadValue(uint8 Copy_u16PreloadVal);

void TIMER1_voidSetPreloadValue(uint16 Copy_u16PreloadVal);

void TIMER2_voidSetPreloadValue(uint8 Copy_u16PreloadVal);

void TIMER0_voidSetCompareMatchValue(uint8 Copy_u16CompMatchVal);

void TIMER1A_voidSetCompareMatchValue(uint16 Copy_u16CompMatchVal);

void TIMER1B_voidSetCompareMatchValue(uint16 Copy_u16CompMatchVal);

void TIMER2_voidSetCompareMatchValue(uint8 Copy_u16CompMatchVal);

void TIMER_void_Int_Enable(uint8 Copy_u8_INT);

void TIMER_void_Int_Disable(uint8 Copy_u8_INT);

uint8 TIMER_u8SetCallBack(uint8 Copy_u8IntSource , void(*Copy_pvCallBackFunc)(void));

void TIMER_voidSetInputCaptureValue(uint16 Copy_u8CompMatchVal);

void TIMER_voidChooseICUTrigger(uint8 Copy_u8Trigger);

uint16 TIMER_u16GetICUValue(void);

#endif
