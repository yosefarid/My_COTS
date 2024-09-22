#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "Service_interface.h"
#include "TIMER_interface.h"




/*--------------------------------------------------------------PWM_Set-----------------------------------------------------------------*/
#define Ticks_Convert_Val 	2000
#define u16Overflow			65535

/*
uint16 Local_u16PT_Result;
uint16 Local_u16PT_Reminder;
uint16 Local_u16OT_Result;
uint16 Local_u16OT_Reminder;
void Pwm_set(void)
{
	static uint16 Local_u16Counter = 0u;
	Local_u16Counter ++;
	TIMER_voidSetInputCaptureValue(0);
	TIMER_voidSetCompareMatchValue(0 , TIMER1A_Comp_Val);

	if(Local_u16Counter == (Local_u16OT_Result + 1 ))
	{
		TIMER_voidSetCompareMatchValue(Local_u16OT_Reminder , TIMER1A_Comp_Val);
	}
	else if(Local_u16Counter == (Local_u16PT_Result + 1 ))
	{
		TIMER_voidSetInputCaptureValue(Local_u16PT_Reminder);
		Local_u16Counter = 0u;
	}
}
 */
// overflow handling missing the max is 32ms
void PWM_voidSet(uint16 Copy_u16PeriodTime_MS, uint16 Copy_u16OnTime_MS)
{
    /* Setting Timer 1 Channel A */
    TIM_1_t Timer1;
    Timer1.Wave_mode = Fast_PWM_ICR;              /**< Timer 1 in Fast PWM mode with ICR1 as top */
    Timer1.Compare_PWM_Mode = Clear_On_Compare;   /**< Clear on compare match */
    Timer1.Channel = Channel_A;                   /**< Using Channel A for PWM output */
    Timer1.Prescaler = DIV_BY_8;                  /**< Set the prescaler to divide clock by 8 */

    TIMER1_u8Init(&Timer1);                       /**< Initialize Timer 1 with the specified configuration */

    /* Check if the period fits within the timer overflow limit */
    if ((Copy_u16PeriodTime_MS * Ticks_Convert_Val) <= u16Overflow)
    {
        /* Set the period (ICR1) and on-time (OCR1A) */
        TIMER_voidSetInputCaptureValue(Copy_u16PeriodTime_MS * Ticks_Convert_Val); /**< Set the period */
        TIMER1A_voidSetCompareMatchValue(Copy_u16OnTime_MS * Ticks_Convert_Val);   /**< Set the on-time */
    }
    /*
    	else
    	{
    		Local_u16PT_Result = (Copy_u16PeriodTime_MS * Ticks_Convert_Val) / u16Overflow;
    		Local_u16PT_Reminder = (Copy_u16PeriodTime_MS * Ticks_Convert_Val) % u16Overflow;

    		if((Copy_u16OnTime_MS * Ticks_Convert_Val) <= u16Overflow)
    		{
    			TIMER_voidSetCompareMatchValue((Copy_u16OnTime_MS * Ticks_Convert_Val) , TIMER1A_Comp_Val);
    		}
    		else
    		{
    			Local_u16OT_Result = (Copy_u16OnTime_MS * Ticks_Convert_Val) / u16Overflow;
    			Local_u16OT_Reminder = (Copy_u16OnTime_MS * Ticks_Convert_Val) % u16Overflow;
    		}

    		TIMER_void_Int_Enable(TIMER1_OVF_INT);
    		TIMER_u8SetCallBack(TIMER1_OVF_INT , Pwm_set);
    	}
    	 */
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------ICU_HARDWARE------------------------------------------------------------*/
/**
 * @file pwm_measurement.c
 * @brief This file contains functions to measure the period and on-time of a PWM signal using Timer1 in Input Capture Mode (ICU).
 *
 * The code provides functions for setting up Timer1 in Normal mode with ICU interrupt enabled.
 * It captures the rising and falling edges of the PWM signal and calculates the period and on-time.
 */

#define Tick_time    4  /**< Conversion factor to convert timer ticks to microseconds based on prescaler */

/**
 * @var Reading0
 * @brief Stores the first capture value (start of the period).
 */
uint16 Reading0;

/**
 * @var Reading1
 * @brief Stores the second capture value (end of the period/start of on-time).
 */
uint16 Reading1;

/**
 * @var Reading2
 * @brief Stores the third capture value (end of on-time).
 */
uint16 Reading2;

uint16* PeriodTime = NULL;  /**< Pointer to store the calculated period time in microseconds */
uint16* OnTime = NULL;      /**< Pointer to store the calculated on-time in microseconds */

/**
 * @brief ICU hardware interrupt handler function.
 *
 * This function is called in the ICU interrupt to capture the rising and falling edges of the PWM signal.
 * It stores the timer values at each edge and calculates the period and on-time of the PWM signal.
 *
 * @note The timer values are captured using the Input Capture Unit (ICU) of Timer1.
 */
void ICU_HW(void)
{
    volatile static uint16 Local_u16Counter = 0u;  /**< Static counter to track which edge is being processed */
    Local_u16Counter++;

    if(Local_u16Counter == 1u)
    {
        Reading0 = TIMER_u16GetICUValue();  /**< Capture the timer value at the first rising edge */
    }
    else if(Local_u16Counter == 2u)
    {
        Reading1 = TIMER_u16GetICUValue();  /**< Capture the timer value at the second rising edge */
        *PeriodTime = (Reading1 - Reading0) * Tick_time;  /**< Calculate the period in microseconds */
        TIMER_voidChooseICUTrigger(Falling_edge);  /**< Switch to falling edge detection to capture on-time */
    }
    else if(Local_u16Counter == 3u)
    {
        Reading2 = TIMER_u16GetICUValue();  /**< Capture the timer value at the falling edge */
        *OnTime = (Reading2 - Reading1) * Tick_time;  /**< Calculate the on-time in microseconds */
        TIMER_void_Int_Disable(TIMER1_ICU_INT);  /**< Disable ICU interrupt after the measurement is complete */
    }
}

uint8 PWM_u8Get(uint16* Copy_pu16PeriodTime_MS, uint16* Copy_pu16OnTime_MS)
{
    uint8 Local_u8ErrState = OK;

    if((Copy_pu16PeriodTime_MS != NULL) && (Copy_pu16OnTime_MS != NULL))
    {
        PeriodTime = Copy_pu16PeriodTime_MS;  /**< Assign the input period time pointer */
        OnTime = Copy_pu16OnTime_MS;          /**< Assign the input on-time pointer */

        /* Initialize Timer1 in normal mode for ICU functionality */
        TIM_1_t Timer1;
        Timer1.Wave_mode = NORMAL;           /**< Normal mode for capturing edges */
        Timer1.Channel = Channel_B;          /**< Use Channel B for input capture */
        Timer1.Prescaler = DIV_BY_64;        /**< Set prescaler to divide clock by 64 */

        TIMER1_u8Init(&Timer1);              /**< Initialize Timer1 with the above configuration */

        TIMER_void_Int_Enable(TIMER1_ICU_INT);  /**< Enable the ICU interrupt for Timer1 */
        TIMER_voidChooseICUTrigger(rising_edge);  /**< Start by detecting the rising edge */
        TIMER_u8SetCallBack(TIMER1_ICU_INT, ICU_HW);  /**< Set the callback function for ICU interrupt */
    }
    else
    {
        Local_u8ErrState = NULL_PTR_ERR;  /**< Return error if any input pointer is NULL */
    }

    return Local_u8ErrState;  /**< Return error state */
}


/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------Schedule_MS-------------------------------------------------------------*/

/**
 * @file schedule_timer.c
 * @brief This file contains functions to schedule periodic or one-time tasks using Timer0 in CTC mode.
 *
 * The code provides functions to configure Timer0 in CTC mode with a compare match interrupt to execute
 * a given task either periodically or once after a specified delay in milliseconds.
 */

uint16 ticks;                 /**< Stores the number of timer ticks required to match the specified time */
uint8 Condition;              /**< Stores the condition (periodic or one-time execution) */
void(*CopyPtrFunc)(void) = NULL;   /**< Function pointer to the user-defined task to execute */

/**
 * @brief Timer0 compare match interrupt service routine.
 *
 * This function is called when Timer0 reaches the compare match value. It increments the internal counter,
 * checks if the scheduled time has elapsed, and then executes the user-defined function. If the task is
 * periodic, the counter is reset to schedule the task again; otherwise, the task is executed only once.
 */
void TIMER_SET(void)
{
    static uint16 Local_u16Counter = 0u;  /**< Internal counter to track elapsed time */
    Local_u16Counter++;

    if(Local_u16Counter == ticks)
    {
        CopyPtrFunc();  /**< Execute the user-defined function */

        if(Condition == periodic)  /**< Check if the task is periodic */
        {
            Local_u16Counter = 0;  /**< Reset the counter for the next execution */
        }
        else
        {
            /* Do nothing for one-time tasks */
        }
    }
}

uint8 Schedule_MS(uint16 Copy_u16Time_MS, uint8 Copy_u8Condition, void(*Copy_pvPtrFunc)(void))
{
    uint8 Local_u8ErrState = OK;

    if(Copy_pvPtrFunc != NULL)
    {
        ticks = Copy_u16Time_MS;       /**< Set the number of ticks for the scheduled time */
        CopyPtrFunc = Copy_pvPtrFunc;  /**< Set the function pointer to the user-defined task */
        Condition = Copy_u8Condition;  /**< Set the condition (one-time or periodic) */

        /* Setting Timer 0 */
        TIM_0_2_t Timer0;
        Timer0.Wave_mode = CTC;               /**< Set Timer0 to CTC mode */
        Timer0.Compare_Mode = Normal_COM;     /**< Normal compare output mode */
        Timer0.Prescaler = DIV_BY_64;         /**< Set the prescaler to divide clock by 64 */

        TIMER0_u8Init(&Timer0);               /**< Initialize Timer0 with the above configuration */

        TIMER0_voidSetCompareMatchValue(250u);  /**< Set the compare match value for Timer0 */
        TIMER_void_Int_Enable(TIMER0_OC_INT);   /**< Enable the compare match interrupt for Timer0 */
        TIMER_u8SetCallBack(TIMER0_OC_INT, TIMER_SET);  /**< Set the callback function for the interrupt */
    }
    else
    {
        Local_u8ErrState = NULL_PTR_ERR;  /**< Return error if the function pointer is NULL */
    }

    return Local_u8ErrState;  /**< Return the error state */
}


/*--------------------------------------------------------------------------------------------------------------------------------------*/

